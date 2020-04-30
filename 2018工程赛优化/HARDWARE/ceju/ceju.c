#include "xunji.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "remote.h"
#include "ceju.h"
#include "adc2.h"

extern unsigned long pwm,pwmup;
extern u16 distance;
extern u8 key;
extern unsigned long time;
u16 cz=0;			//jiasudu    »ý·ÖÖµ
u16 distance_last=315;
u16 jizhun=315;//312
long left=0;
long right=0;
float kkp=0.01,kkd=0.2;

void ceju1(void)
{
//	delay_ms(2);
	key = Remote_Scan();
//	distance = jizhun;
	distance = extremaverage(ADC_Channel_10,9)/10;
	cz = (distance-distance_last)/10;
	distance_last = distance;
	

		left=pwm*8+(distance-jizhun)*kkp*pwm+cz*kkd*pwm+pwm/100*pwm/100*pwm/100*pwm/100/50;//+cz*kkd*pwm+pwm/100*pwm/100*pwm/100*pwm/100/50;
		right=pwm*8-(distance-jizhun)*kkp*pwm+cz*kkd*pwm;
	
//	  left=pwm*8;
//		right=pwm*8;
		
//	if(distance<=85)
//	{
//		left=0;
//		right=400;
//	}
//	if(distance>=85)
//	{
//		left=400;
//		right=0;
//	}
	if(left>6800)
		left = 6800;
	if(right>6800)
		right =6800;
	if(left<10)
		left=10;
	if(right<10)
		right=10;
	speed1(left,right);	
}	

void ceju(void)
{
	ceju1();
	pwm=pwm+3;

	if(pwm>pwmup)
	{
		pwm=pwmup;
	}
	if(key==152)//2
	{
		while(1)
		{
		 ceju1();
     pwm=pwm-1;
		 delay_us(100);
     if(pwm<100)
		 {
		   break;
		 }			 
		}
		while(1)
    {
     	key=Remote_Scan();
	    if(key==24)//5
			{
			 pwm=0;			
			 break;
			}
      tingzhi(); 		
		}			
	}
	
}





























