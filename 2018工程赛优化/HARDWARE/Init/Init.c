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
  delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	LED_Init(); //LED端口初始化
  Adc_Init();
	GPIO_Config();
	pwm_Init(); 
	Remote_Init();			//红外接收初始化 
	TIM2_PWM_Init(7199,0);	 //不分频。PWM频率=72000000/900=80Khz
	TIM3_PWM_Init(1999,719);
	GPIOD_Init();
//	TIM4_PWM_Init(1999,719);
	yanse_init();
	
}

