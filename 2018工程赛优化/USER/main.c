#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "remote.h"
#include "xunji.h"
#include "Init.h"
#include "duoj.h"
#include "math.h"
#include "fenduan.h"
#include "movements.h"
#include "ceju.h"
#include "rgb3.h"

//#define aaa
//#define ABS(x) ((x)>=0?(x):-(x))
/************************************************
���⣺
	1->104
	2->152
	5->24
	
************************************************/
/************************************************
Pin
	��ɫ��
		S0  - GND
		S1  - 5V
		S2  - PD10
		S3  - PD11
		E0  - GND
		OUT - PE2
		
	���� PB9 
	
	�����
		PC6 - #1
		PC7 - #2	
		PC8 - #3
		PC9 - #4
	
	С�����//97--170   ���������
	  
	�����
		PA2 - TIM2_CH3
		PA3 - TIM2_CH4
		PA5-8
		
	CCD��
		SI  - PA4
		CLK - PA0
		A0  - PA1
		
	��������6ɫ��4����
    ɫ��ǰ - PB4
		
		��ɫ�� - PE0
		��ɫ�� - PE1
		
		����� - PB7
		�ұ��� - PE3
		
		�ϰ�   - PE4
		
		�м��� - PE5
		�м��� - PC1
		
		��Ҷ� - PE8
		�һҶ� - PE7
		
		��ɫ�� - PE9
		�Թ���� - PB6
		
		
	�ƣ�
		��1 - PC2
		��2 - PC3
		//��3 - PE9
		
************************************************/
extern unsigned long pwm=0,pwmup=300;
extern int time=0,yanse=0,yansexuan=2;//��ɫ�޸�
extern u8 key=0;
extern u16 adcx=64;
extern int duan=0;
extern u8 distance=0;
int cc;

void ceshi()
{
	while(1)
	{
		duoji();
	}
}


int main(void)
{
	Init();
	while(1)
	{
		xunji();
	}
//	while(1)
//	{
//		duoji1234kuai(147,145,212,116);//��������	
//	}
//	jiasudao(400);
//	yunsu(400,400);
//	while(1)
//	{
//		ceju();
//		if(rukou==0)
//		{
//			jiansudao(100);
//			ting();
//		}
//	}
//while(1)
//{
//	#ifdef aaa
//	led(0);
//	#else
//	led(2);
//	#endif
//}
//	while(1)
//	{
//		fangwuliao();
//	}
	xiaoduoji(2);
	duoji1234kuai(147,66,112,74);//����
//	
//	while(1)
//	{
//		key = Remote_Scan();
//		if(key == 152)//��2
//		{
//			xuanyanse();
////			zhuawuliao();			
//			break;
//		}	
//	}
//	while(1)
//	{
//		led(0);
//		delay_ms(1000);
//		led(2);
//		delay_ms(1000);
//	}
/*************ֻѭ��*********
	while(1)
	{
//		zhijiaoyou(300,300,10000);
		 key=Remote_Scan();
		 adcx=CCD_Find();	
//			if(qianyou==0)
//	{
//		ting();
//	}
		 if(key==24)
		 {
			 while(1)
			 {		 
				 xunji();
				 time++;
//				 	if(sebiaoyou==0&&cc==0)
//					{
//						zhuanxiang(480,60,450);
//						cc=1;
//						ting();						
//					}
//					else if(sebiaoyou==0&&cc==1)
//					{
//						zhuanxiang(450,50,500);
//						ting();
//					}
//					if(time>3000)
//						ting();
				 if(sebiaozuo==0)
				 {
					 jiansu3(100);
					 pwmup=100;
				 }
					if(zhongjianzuo==0&&cc==0)
					{
						duanting(500);
						zhijiaozuo(300,300,320);
						jiasu2(300);
						pwmup=300;
						cc=1;
//						ting();
					}
					else if(zhongjianzuo==0&&cc==1)
					{
						duanting(500);
						zhijiaozuo(300,300,320);
						ting();
					}
//					if(qianzuo==0)
//					{
//						zhijiaozuoguai(5400,1200);
//						delay_ms(520);
//						ting();
//					}
				}
		 }
	 }
******************************/
	while(1)
	{
		key=Remote_Scan();
		if(key==24)//��5
		{
//			while(1)
//			{
//				ceju();
//				if(rukou==0)
//				{
//					while(1)
//					{
//						xunji();
//					}
//				}
//			}
//			led(1);//2������
			while(1)
			{
				switch(duan)
				{
					case 0: zero();break;//
					case 1: one();break;//
					case 2: two();break;//
					case 3: three();break;//
					case 4: four();break;//
					case 5: five();break;//
					case 6: six();break;//
					case 7: seven();break;//
					case 8: eight();break;//
					case 9: nine();break;//
					case 10: ten();break;//
					case 11: eleven();break;//
				}
			}
		}
	}
}

