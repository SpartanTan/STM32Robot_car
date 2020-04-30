#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "duoj.h"
#include "math.h"
#include "stdio.h"

/******舵机******
	 		PC6->#1
			PC7->#2	
			PC8->#3
			PC9->#4
	
			PD9->小舵机
第1级，从车头看，大向左，小向右，147在正中	
			
			收纳位置：
			1-147
			2-60
			3-116
			4-74
				
			第一排正上位置：
			147
			120
			250
			95
			
			116
			250
			100
			
			第一排下去：
			147
			156
			249
			74
			
			
			第二排正上：
			147
			128
			234
			102
			
			第二排下去：
			147
			158
			232
			86
			
			第三排正上：
			147
			145
			212
			116（抬起时118)
			
			第三排下去：
			147
			165
			210
			104
			
			
*******************/
void GPIOD_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_6;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);						
}


void TIM3_PWM_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9 ;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
		
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//GPIO_FullRemap_TIM3   GPIO_PartialRemap_TIM3
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC3Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC4Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable); 
	TIM_Cmd(TIM3,ENABLE); 
}
//int gongyueshu(u16 duo2_set,u16 duo3_set,u16 duo4_set)
//{	
//	u16 gongyueshu1=0,gongyueshu2=0;
//	while(duo2_set!=duo3_set)
//		if(duo2_set>duo3_set)
//			duo2_set=duo2_set-duo3_set;
//		else
//			duo3_set=duo3_set-duo2_set;
//	gongyueshu1=duo3_set;
//	while(gongyueshu1!=duo4_set)
//		if(gongyueshu1>duo4_set)
//			gongyueshu1=gongyueshu1-duo4_set;
//		else
//			duo4_set=duo4_set-gongyueshu1;	
//	gongyueshu2=duo4_set;	
//	return gongyueshu2;		
//}

	//线在远端，从金属看进去，数字越小越卷曲                                                                                                                                                        越大，逆时针
	//第一级舵机200调平，
u16 duo1,duo2,duo3,duo4;
void mantiao(u16 duo2_set,u16 duo3_set,u16 duo4_set)
{
	int cz2,cz3,cz4;
	int ccz2,ccz3,ccz4;
	int gongyueshu1=0,gongyueshu2=0;
	int duoji2_mod=0,duoji3_mod=0,duoji4_mod=0;//1为增加、放下，0为减少、卷曲
	int i=0;
//	u16 gongyueshu=0;

	
	if(duo2>duo2_set)
	{
		cz2=duo2-duo2_set;
		duoji2_mod=0;//卷曲
	}
	else
	{
		cz2=duo2_set-duo2;
		duoji2_mod=1;//放下
	}
	if(duo3>duo3_set)
	{
		cz3=duo3-duo3_set;
		duoji3_mod=0;
	}
	else
	{
		cz3=duo3_set-duo3;
		duoji3_mod=1;
	}
	if(duo4>duo4_set)
	{
		cz4=duo4-duo4_set;
		duoji4_mod=0;
	}
	else
	{
		cz4=duo4_set-duo4;
		duoji4_mod=1;
	}
	
	ccz2=cz2;
	ccz3=cz3;
	ccz4=cz4;
	
//	printf("cz2=%d",cz1);
//解算公约数	
	while(cz2!=cz3)
		if(cz2>cz3)
			cz2=cz2-cz3;
		else
			cz3=cz3-cz2;
	gongyueshu1=cz3;
	while(gongyueshu1!=cz4)
		if(gongyueshu1>cz4)
			gongyueshu1=gongyueshu1-cz4;
		else
			cz4=cz4-gongyueshu1;	
	gongyueshu2=cz4;	
	
//		printf("公约数=%d\r\n",gongyueshu2);
		
	for(i=1;i<=(gongyueshu2*2);i++)
	{
		if(duoji4_mod==1)
			TIM_SetCompare4(TIM3,duo4+i*(ccz4/gongyueshu2)/2);
		else if(duoji4_mod==0)
			TIM_SetCompare4(TIM3,duo4-i*(ccz4/gongyueshu2)/2);
		if(duoji2_mod==1)
			TIM_SetCompare2(TIM3,duo2+i*(ccz2/gongyueshu2)/2);
		else if(duoji2_mod==0)
			TIM_SetCompare2(TIM3,duo2-i*(ccz2/gongyueshu2)/2);
		if(duoji3_mod==1)
			TIM_SetCompare3(TIM3,duo3+i*(ccz3/gongyueshu2)/2);
		else if(duoji3_mod==0)
			TIM_SetCompare3(TIM3,duo3-i*(ccz3/gongyueshu2)/2);
		
		delay_ms(50);
//		printf("舵机4角度=%d\r\n",duo4-i*(ccz4/gongyueshu2));
	}
	duo2=duo2_set;
	duo3=duo3_set;
	duo4=duo4_set;
}

void mantiao1(u16 duo2_set,u16 duo3_set,u16 duo4_set)
{
	int cz2,cz3,cz4;
	int ccz2,ccz3,ccz4;
	int gongyueshu1=0,gongyueshu2=0;
	int duoji2_mod=0,duoji3_mod=0,duoji4_mod=0;//1为增加、放下，0为减少、卷曲
	int i=0;
//	u16 gongyueshu=0;

	
	if(duo2>duo2_set)
	{
		cz2=duo2-duo2_set;
		duoji2_mod=0;//卷曲
	}
	else
	{
		cz2=duo2_set-duo2;
		duoji2_mod=1;//放下
	}
	if(duo3>duo3_set)
	{
		cz3=duo3-duo3_set;
		duoji3_mod=0;
	}
	else
	{
		cz3=duo3_set-duo3;
		duoji3_mod=1;
	}
	if(duo4>duo4_set)
	{
		cz4=duo4-duo4_set;
		duoji4_mod=0;
	}
	else
	{
		cz4=duo4_set-duo4;
		duoji4_mod=1;
	}
	
	ccz2=cz2;
	ccz3=cz3;
	ccz4=cz4;
	
//	printf("cz2=%d",cz1);
//解算公约数	
	while(cz2!=cz3)
		if(cz2>cz3)
			cz2=cz2-cz3;
		else
			cz3=cz3-cz2;
	gongyueshu1=cz3;
	while(gongyueshu1!=cz4)
		if(gongyueshu1>cz4)
			gongyueshu1=gongyueshu1-cz4;
		else
			cz4=cz4-gongyueshu1;
	gongyueshu2=cz4;
	
//		printf("公约数=%d\r\n",gongyueshu2);
		
	for(i=1;i<=gongyueshu2;i++)
	{
		if(duoji2_mod==1)
			TIM_SetCompare2(TIM3,duo2+i*(ccz2/gongyueshu2));
		else if(duoji2_mod==0)
			TIM_SetCompare2(TIM3,duo2-i*(ccz2/gongyueshu2));
		if(duoji3_mod==1)
			TIM_SetCompare3(TIM3,duo3+i*(ccz3/gongyueshu2));
		else if(duoji3_mod==0)
			TIM_SetCompare3(TIM3,duo3-i*(ccz3/gongyueshu2));
		if(duoji4_mod==1)
			TIM_SetCompare4(TIM3,duo4+i*(ccz4/gongyueshu2));
		else if(duoji4_mod==0)
			TIM_SetCompare4(TIM3,duo4-i*(ccz4/gongyueshu2));
		delay_ms(300);
//		printf("舵机4角度=%d\r\n",duo4-i*(ccz4/gongyueshu2));
	}
	duo2=duo2_set;
	duo3=duo3_set;
	duo4=duo4_set;
}
void duoji1234(u16 one,u16 two,u16 three,u16 four)
{
	duo1 = one;
	duo2 = two;
	duo3 = three;
	duo4 = four;
	
	TIM_SetCompare1(TIM3,duo1);
	
	TIM_SetCompare2(TIM3,duo2);
	delay_ms(500);
	TIM_SetCompare3(TIM3,duo3); //50-250
	delay_ms(500);
	TIM_SetCompare4(TIM3,duo4);
	delay_ms(500);
}
void duoji1234kuai(u16 one,u16 two,u16 three,u16 four)
{
	duo1 = one;
	duo2 = two;
	duo3 = three;
	duo4 = four;
	
	TIM_SetCompare1(TIM3,duo1);
	
	TIM_SetCompare2(TIM3,duo2);
	delay_ms(100);
	TIM_SetCompare3(TIM3,duo3); //50-250
	delay_ms(100);
	TIM_SetCompare4(TIM3,duo4);
	delay_ms(100);
}
void duoji2341(u16 one,u16 two,u16 three,u16 four)
{
	duo1 = one;
	duo2 = two;
	duo3 = three;
	duo4 = four;
	
	TIM_SetCompare2(TIM3,duo2);
	delay_ms(500);
	TIM_SetCompare3(TIM3,duo3); //50-250
	delay_ms(500);
	TIM_SetCompare4(TIM3,duo4);
	delay_ms(500);
	TIM_SetCompare1(TIM3,duo1);
	delay_ms(500);
}
void duoji3412(u16 one,u16 two,u16 three,u16 four)
{
	duo1 = one;
	duo2 = two;
	duo3 = three;
	duo4 = four;
	
	TIM_SetCompare3(TIM3,duo3); //50-250
	delay_ms(500);
	TIM_SetCompare4(TIM3,duo4);
	delay_ms(500);
	TIM_SetCompare1(TIM3,duo1);
	delay_ms(500);
	TIM_SetCompare2(TIM3,duo2);
	delay_ms(500);
}
void duoji3412kuai(u16 one,u16 two,u16 three,u16 four)
{
	duo1 = one;
	duo2 = two;
	duo3 = three;
	duo4 = four;
	
	TIM_SetCompare3(TIM3,duo3); //50-250
	delay_ms(100);
	TIM_SetCompare4(TIM3,duo4);
	delay_ms(100);
	TIM_SetCompare1(TIM3,duo1);
	delay_ms(100);
	TIM_SetCompare2(TIM3,duo2);
	delay_ms(100);
}
void duoji1324(u16 one,u16 two,u16 three,u16 four)
{
		duo1 = one;
		duo2 = two;
		duo3 = three;
		duo4 = four;
	
	TIM_SetCompare1(TIM3,duo1);
	
	TIM_SetCompare3(TIM3,duo3);
		delay_ms(1000);
	TIM_SetCompare2(TIM3,duo2);
		delay_ms(1000);
	TIM_SetCompare4(TIM3,duo4); //50-250
		delay_ms(1000);
	
}
void duoji1342(u16 one,u16 two,u16 three,u16 four)
{
		duo1 = one;
		duo2 = two;
		duo3 = three;
		duo4 = four;
	
	TIM_SetCompare1(TIM3,duo1);//149
	
	TIM_SetCompare3(TIM3,duo3);
		delay_ms(2000);
	TIM_SetCompare4(TIM3,duo4); //50-250
		delay_ms(2000);
	TIM_SetCompare2(TIM3,duo2);
		delay_ms(2000);

	
}
void duoji1243(u16 one,u16 two,u16 three,u16 four)
{
		duo1 = one;
		duo2 = two;
		duo3 = three;
		duo4 = four;
	
	TIM_SetCompare1(TIM3,duo1);
	
	TIM_SetCompare2(TIM3,duo2);
	delay_ms(500);
	TIM_SetCompare4(TIM3,duo4);
	delay_ms(500);
	TIM_SetCompare3(TIM3,duo3); //50-250
	delay_ms(500);
}

void duoji2(u16 x,u16 y,u16 z)
{
	duo1 = x;
	duo2 = y;
	duo3 = z;
	TIM_SetCompare3(TIM3,duo3);
	TIM_SetCompare2(TIM3,duo2); //50-250
	TIM_SetCompare1(TIM3,duo1);	
}
void delay(u16 x)
{
	int i;
	for(i=0;i<x;i++)
	{
		delay_ms(1000);
	}
}

void manfang2(u16 angle)
{
	u16 p;
	for(p=duo2;p<(angle+1);p++)
	{
		TIM_SetCompare2(TIM3,p);
		delay_ms(100);
	}
}
void duoji(void)
{		
	duoji1342(147,60,116,75);//收起
	manfang2(147);
//	duoji1243(120,250,95);
	delay_ms(1000);
	delay_ms(1000);
	duoji1234(147,120,250,95);//第一排
//	
//	delay_ms(1000);
//	delay_ms(1000);
//	
////	duoji1234(90,250,95);
////	TIM_SetCompare2(TIM3,90);
//	
////	delay_ms(1000);
//	delay_ms(1000);
//	
	
//	duoji1342(147,213,110);
//	delay_ms(1000);
//	delay_ms(1000);
//	duoji1342(170,204,110);
	
//	duoji1324(155,205,120);
//	while(1);

}
void xiaoduoji(int mod)
{
	
	int time=0;
//	TIM_SetCompare3(TIM4,97); //97-170
//	delay_ms(1000);
//	delay_ms(1000);
//	TIM_SetCompare3(TIM4,170); //97-170	
	
//	PDout(6)=1;
//	delay_us(970);
//	PDout(6)=0;
//	delay_ms(19);
//	
//	delay_ms(1000);
//	delay_ms(1000);
//
	if(mod==1)//松
	{
		for(time=0;time<50;time++)
		{	
			PDout(9)=1;
			delay_ms(1);
			delay_us(850);
			PDout(9)=0;
			delay_ms(18);
			delay_us(150);
		}
	}
	else if(mod==2)//紧
	{
		for(time=0;time<50;time++)
		{	
			PDout(9)=1;
			delay_us(850);
			PDout(9)=0;
			delay_ms(19);
			delay_us(150);
		}
	}
	
//	delay_ms(1000);
//	delay_ms(1000);
}


