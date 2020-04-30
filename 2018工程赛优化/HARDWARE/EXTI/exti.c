#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 								  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
extern u16 pwm;
extern u16 a=0;
extern u16 b=0;
extern u16 c=0;
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOE.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

//外部中断2服务程序
void EXTI2_IRQHandler(void)            //前色标传感器  E.2
{
	delay_ms(1);//消抖
	if(KEY2==0)	  //按键KEY2
	{ if(a==0)
		{
		LED1=!LED1;
		a=1;	
		tingzhi();
		delay_ms(50);			
    pwm=80;
    }
    if(a==5)
    {
     LED1=!LED1;
     a=0;
     delay_ms(100);			
		}			
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)           //左色标传感器    E.3
{
	delay_ms(10);//消抖
	if(KEY1==0&&a==1)	 //按键KEY1
	{	delay_ms(10);			 
		LED1=!LED1;
		a=2;
		c++;
		tingzhi();
    delay_ms(50);
		while(a==2)
		{			
		zhijiaozuo();
		delay_ms(5);
			b++;
		if(zuosebiao==0&&b>35)
		{	
	  pwm=180;
		b=0;
		a=0;			
		}		
		}
	}
  EXTI_ClearITPendingBit(EXTI_Line2);	
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI4_IRQHandler(void)           //避障传感器   E.4
{
	delay_ms(10);//消抖
	if(KEY0==0)	 //按键KEY0
	{
		LED1=!LED1; 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}
 
