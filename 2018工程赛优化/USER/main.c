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
红外：
	1->104
	2->152
	5->24
	
************************************************/
/************************************************
Pin
	颜色：
		S0  - GND
		S1  - 5V
		S2  - PD10
		S3  - PD11
		E0  - GND
		OUT - PE2
		
	红外 PB9 
	
	舵机：
		PC6 - #1
		PC7 - #2	
		PC8 - #3
		PC9 - #4
	
	小舵机：//97--170   最紧，最松
	  
	电机：
		PA2 - TIM2_CH3
		PA3 - TIM2_CH4
		PA5-8
		
	CCD：
		SI  - PA4
		CLK - PA0
		A0  - PA1
		
	传感器：6色标4避障
    色标前 - PB4
		
		左色标 - PE0
		右色标 - PE1
		
		左避障 - PB7
		右避障 - PE3
		
		障碍   - PE4
		
		中间左 - PE5
		中间右 - PC1
		
		左灰度 - PE8
		右灰度 - PE7
		
		后色标 - PE9
		迷宫入口 - PB6
		
		
	灯：
		灯1 - PC2
		灯2 - PC3
		//灯3 - PE9
		
************************************************/
extern unsigned long pwm=0,pwmup=300;
extern int time=0,yanse=0,yansexuan=2;//颜色修改
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
//		duoji1234kuai(147,145,212,116);//第三排上	
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
	duoji1234kuai(147,66,112,74);//收纳
//	
//	while(1)
//	{
//		key = Remote_Scan();
//		if(key == 152)//按2
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
/*************只循迹*********
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
		if(key==24)//按5
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
//			led(1);//2档亮度
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

