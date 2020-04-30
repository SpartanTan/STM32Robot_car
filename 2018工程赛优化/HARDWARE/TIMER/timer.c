#include "timer.h"
#include "led.h"
#include "usart.h"
#include "adc.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 								  
//********************************************************************************
//������� PA5-8
//    ����ǰ�� 5��6��
//    ����ǰ�� 7��8��
//
//pwm PA2-3	
//    �ң�PA2->TIM2_CH3  ����
//    ��PA3->TIM2_CH4  ����
//////////////////////////////////////////////////////////////////////////////////  
   	  
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void pwm_Init(void)//�������PA5->8
{
	GPIO_InitTypeDef GPIOInitstructure; 
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOInitstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitstructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_8;
	GPIOInitstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOA,&GPIOInitstructure);
}



//TIM2 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ�ܶ�ʱ��2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
   //���ø�����Ϊ�����������,���TIM2 CH3,CH4��PWM���岨��	GPIOA.2|3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
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
	
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM3

}

void speed1(u16 zuo,u16 you)
{
		TIM_SetCompare3(TIM2,you);//����
		TIM_SetCompare4(TIM2,zuo);//����
	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);//��ǰ�� 5��6��
	  GPIO_SetBits(GPIOA,GPIO_Pin_7);//��ǰ�� 7��8��
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
	TIM_SetCompare3(TIM2,you*8);//����
	TIM_SetCompare4(TIM2,zuo*8);//����
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}

void daoche(u16 zuo,u16 you)
{
	TIM_SetCompare3(TIM2,you*8);//����
	TIM_SetCompare4(TIM2,zuo*8);//����
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

void yuandizuozhuan(u16 zuo,u16 you)//ԭ����ת
{
	TIM_SetCompare3(TIM2,you*8);//����
	TIM_SetCompare4(TIM2,zuo*8);//����
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
void yuandiyouzhuan(u16 zuo,u16 you)//ԭ����ת
{
	TIM_SetCompare3(TIM2,you*8);//����
	TIM_SetCompare4(TIM2,zuo*8);//����
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}




