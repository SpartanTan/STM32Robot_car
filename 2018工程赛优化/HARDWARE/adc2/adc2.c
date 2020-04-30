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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}

//获得ADC值
//ch:通道值 0~3

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
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
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
	for(samplecnt=0;samplecnt<times;samplecnt++)//测8次，samp=8
	{
		rlevelsum += Get_Adc_Average(ADC_Channel_10,4);//Get_Adc(ADC_Channel_10);
	}
	rlevelsum = rlevelsum - rlevelsum/samplecnt + Get_Adc(ADC_Channel_10);//Get_Adc_Average(ADC_Channel_10,9);
	return rlevelsum/times;
}

