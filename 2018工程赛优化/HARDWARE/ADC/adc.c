 #include "adc.h"
 #include "delay.h"
 #include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 					  
////////////////////////////////////////////////////////////////////////////////// 
u16 Exposure_tim=0;
u8 ao_d[128]={0},u[128];
//初始化GPIO
//将引脚PA4，PA0设置为输出状态
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIOInitstructure; 
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOInitstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4;
	GPIOInitstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOA,&GPIOInitstructure);
}		 
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef  ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
 

//	RCC_HCLKConfig(RCC_SYSCLK_Div4);//设置AHB时钟
//	RCC_PCLK2Config(RCC_HCLK_Div1);//设置高速AHB时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

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
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
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
	int n,find=64;  //Exposure_tim为曝光时间，单位时间为2us，这里设置为9879即为曝光20ms
	
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
		if(ao_d[n]<250)//白线拉高  黑线拉低
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
//  for(n=0;n<Exposure_tim;n++)//曝光
//	{
//		delay_us(1);
//		CLK(1);		
//		delay_us(1);
//		CLK(0);		
//  }
	for(n=0;n<128;n++)//取中点
	{
	 if(ao_d[n]==255)
	 {
    b[a]=n;
    a++;		 
	 }
	}
	find=b[a/2];
//  SendImageData(ao_d);  //左旋变大  右旋变小
	return find;	
}

	





















