 #include "adc.h"
 #include "delay.h"
 #include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 					  
////////////////////////////////////////////////////////////////////////////////// 
u16 Exposure_tim=0;
u8 ao_d[128]={0},u[128];
//��ʼ��GPIO
//������PA4��PA0����Ϊ���״̬
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIOInitstructure; 
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOInitstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4;
	GPIOInitstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOA,&GPIOInitstructure);
}		 
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef  ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

//	RCC_HCLKConfig(RCC_SYSCLK_Div4);//����AHBʱ��
//	RCC_PCLK2Config(RCC_HCLK_Div1);//���ø���AHBʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

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
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 ch,u8 times)
{ 
	u8 temp_val[3];
	u8 t,y,k;
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
}

void SI(int a)
{
//		 GPIO_Config();
	if(a==1)
	{	
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	}
	else if(a==0)
	{	
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
}

void CLK(int a)
{
//		 GPIO_Config();
	if(a==1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
	}
	else if(a==0)
	{	
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	}		
}
	
u16 CCD_Find(void)
{
	u8 ao_d[128];
	int a=0,b[128]={64};
	int n,find=64;  //Exposure_timΪ�ع�ʱ�䣬��λʱ��Ϊ2us����������Ϊ9879��Ϊ�ع�20ms
	
	SI(0);
	CLK(0);
  delay_us(1);
	SI(1);
	
	for(n=0;n<128;n++)
	{
		delay_us(1);
		CLK(1);
    SI(0);		
		delay_us(1);
		ao_d[n]=Get_Adc_Average(1,3);
		CLK(0);
		if(ao_d[n]<250)//��������  ��������
		{ao_d[n]=0;
		ao_d[n-1]=0;
//		ao_d[n-3]=0;
//    ao_d[n+3]=0;			
		ao_d[n-2]=0;
		ao_d[n+1]=0;
		ao_d[n+2]=0;
		}
   else 
		ao_d[n]=255;
 }
	delay_us(1);
  CLK(1);
	delay_us(1);
	CLK(0);
//  for(n=0;n<Exposure_tim;n++)//�ع�
//	{
//		delay_us(1);
//		CLK(1);		
//		delay_us(1);
//		CLK(0);		
//  }
	for(n=0;n<128;n++)//ȡ�е�
	{
	 if(ao_d[n]==255)
	 {
    b[a]=n;
    a++;		 
	 }
	}
	find=b[a/2];
//  SendImageData(ao_d);  //�������  ������С
	return find;	
}

	





















