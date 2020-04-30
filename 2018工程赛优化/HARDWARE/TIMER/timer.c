#include "timer.h"
#include "led.h"
#include "usart.h"
#include "adc.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 								  
//********************************************************************************
//电机开关 PA5-8
//    右轮前进 5低6高
//    左轮前进 7高8低
//
//pwm PA2-3	
//    右：PA2->TIM2_CH3  右轮
//    左：PA3->TIM2_CH4  左轮
//////////////////////////////////////////////////////////////////////////////////  
   	  
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void pwm_Init(void)//电机开关PA5->8
{
	GPIO_InitTypeDef GPIOInitstructure; 
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOInitstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitstructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_8;
	GPIOInitstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOA,&GPIOInitstructure);
}



//TIM2 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM2 CH3,CH4的PWM脉冲波形	GPIOA.2|3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
	
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM2, ENABLE);  //使能TIM3

}

void speed1(u16 zuo,u16 you)
{
		TIM_SetCompare3(TIM2,you);//右轮
		TIM_SetCompare4(TIM2,zuo);//左轮
	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);//左前进 5低6高
	  GPIO_SetBits(GPIOA,GPIO_Pin_7);//右前进 7高8低
	  GPIO_SetBits(GPIOA,GPIO_Pin_6);
	  GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void tingzhi(void)
{
    TIM_SetCompare3(TIM2,0);
		TIM_SetCompare4(TIM2,0);
}

void zhuanwan(u16 zuo,u16 you)
{
	TIM_SetCompare3(TIM2,you*8);//右轮
	TIM_SetCompare4(TIM2,zuo*8);//左轮
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void daoche(u16 zuo,u16 you)
{
	TIM_SetCompare3(TIM2,you*8);//右轮
	TIM_SetCompare4(TIM2,zuo*8);//左轮
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

void yuandizuozhuan(u16 zuo,u16 you)//原地左转
{
	TIM_SetCompare3(TIM2,you*8);//右轮
	TIM_SetCompare4(TIM2,zuo*8);//左轮
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
void yuandiyouzhuan(u16 zuo,u16 you)//原地右转
{
	TIM_SetCompare3(TIM2,you*8);//右轮
	TIM_SetCompare4(TIM2,zuo*8);//左轮
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}




