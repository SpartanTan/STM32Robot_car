#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "remote.h"
#include "Init.h"
#include "rgb3.h"
#include "duoj.h"

void Init(void)
{
  delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init(); //LED�˿ڳ�ʼ��
  Adc_Init();
	GPIO_Config();
	pwm_Init(); 
	Remote_Init();			//������ճ�ʼ�� 
	TIM2_PWM_Init(7199,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
	TIM3_PWM_Init(1999,719);
	GPIOD_Init();
//	TIM4_PWM_Init(1999,719);
	yanse_init();
	
}

