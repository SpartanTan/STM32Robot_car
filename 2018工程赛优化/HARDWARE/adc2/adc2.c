#include "xunji.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc2.h"
#include "remote.h"
#include "ceju.h"

void  Adc2_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	ADC_DeInit(ADC1);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}

//���ADCֵ
//ch:ͨ��ֵ 0~3

u16 extremaverage(u8 ch,u8 times)
{
	u16 temp_val[9];
	u16 use_val[7];
	u16 k;
	u8 t,y;
	u16 max=0,min=0,sum=0,average=0;
	
	for(t=0;t<times;t++)
	{
		temp_val[t]=Get_Adc_Average2(ch,3);
//		printf("%d\r\n",temp_val[t]);
//		delay_ms(50);//
	}
	for(t=0;t<times-1;t++)
	{
		for(y=times-1;y>t;y--)
		{
			if(temp_val[y]>=temp_val[y-1])
			{
			 k=temp_val[y];
			 temp_val[y]=temp_val[y-1];
			 temp_val[y-1]=k;				
			}
		}
	}
//	for(t=0;t<times;t++)
//	{
//		printf("%d\r\n",temp_val[t]);
//	}
	max=temp_val[0]+temp_val[1];//+temp_val[2]+temp_val[3];
	min=temp_val[8]+temp_val[7];//+temp_val[12]+temp_val[11];
//	for(t=0;t<times-2;t++)
//	{
//		use_val[t]=temp_val[t+1];
//	}
	for(t=0;t<9;t++)
	{
		sum+=temp_val[t];
	}
//	printf("%d       ",sum);
	average=(sum-max-min)/5;
	
	return average;
}

u16 Get_Adc2(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average2(u8 ch,u8 times)
{
	u32 temp_val[3];
	u8 t,y;
	u16 k;
	for(t=0;t<times;t++)
	{
		temp_val[t]=Get_Adc(ch);
	}
	for(t=0;t<times-1;t++)
	{
		for(y=times-1;y>t;y--)
		{
			if(temp_val[y]>=temp_val[y-1])
			{
				 k=temp_val[y];
				 temp_val[y]=temp_val[y-1];
				 temp_val[y-1]=k;				
			}
		}
	}
	return temp_val[(times+1)/2];
	
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc(ch);
//		delay_ms(5);
//	}
//	return temp_val/times;
}

u16 ADC_Average(u8 times)//9
{
	int samplecnt=0;
	u32 rlevelsum=0;
	for(samplecnt=0;samplecnt<times;samplecnt++)//��8�Σ�samp=8
	{
		rlevelsum += Get_Adc_Average(ADC_Channel_10,4);//Get_Adc(ADC_Channel_10);
	}
	rlevelsum = rlevelsum - rlevelsum/samplecnt + Get_Adc(ADC_Channel_10);//Get_Adc_Average(ADC_Channel_10,9);
	return rlevelsum/times;
}

