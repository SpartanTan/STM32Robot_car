#include "xunji.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "remote.h"
/************************************************
1hao 100 35 5100
1hao 90 30  4800
2hao 130  40  5000
2hao 140  45  5500
************************************************/
extern long pwm,pwmup;
extern u8 key;
extern unsigned long time;
long d=0;			//jiasudu    积分值
long adcx1=64;  //hahahahahahahaha
long zuo=0;
long you=0;
extern long adcx;
float kp=0.275,kd=3.2;	 //2.75，3.2
void xunji1(void)
{
    key=Remote_Scan();
	  adcx=64;			
		adcx=CCD_Find();		
		d=adcx-adcx1;	
    adcx1=adcx;			
		 if(3<adcx<125)
			{
		    zuo=pwm*8+adcx*kp*pwm-64*kp*pwm+d*kd*pwm+pwm/100*pwm/100*pwm/100*pwm/100/50;//左轮   //左右电机差速控制
		    you=pwm*8-adcx*kp*pwm+64*kp*pwm-d*kd*pwm;//+pwm/100*pwm/100*pwm/100*pwm/100*pwm/100/100;//*pwm/100/130//右轮
			}
//			if(15<adcx<31||97<adcx<113)
//			{
//		    zuo=pwm*8+(adcx-64)*0.2*pwm;   //左右电机差速控制
//		    you=pwm*8-(adcx-64)*0.2*pwm+pwm/100*pwm/100*pwm/100*pwm/100*pwm/100/220;
//			}
			
//		 if(3<adcx<25||103<adcx<125)
//			{
//		    zuo=pwm*8+(adcx-64)*0.3*pwm;   //左右电机差速控制
//		    you=pwm*8-(adcx-64)*0.3*pwm+pwm/100*pwm/100*pwm/100*pwm/100*pwm/100/220;			
//			}
			if(zuo>6800)               //上限
			{
			zuo=6800;
			}
			if(you>6800)
			{
			you=6800;
			}
			if(zuo<10)               //xia限
			{
			zuo=10;
			}
			if(you<10)
			{
			you=10;
			}
			
    speed1(zuo,you);			
}

void xunji(void)
{
  xunji1();
	pwm=pwm+4;   //加速起步
	if(pwm>pwmup)
	{
		pwm=pwmup;
	}
	if(key==152)//2
	{
		while(1)
		{
		 xunji1();
     pwm=pwm-4;
     if(pwm<100)
		 {
		   break;
		 }			 
		}
		while(1)
    {
     	key=Remote_Scan();
			adcx=CCD_Find();
	    if(key==24)//5
			{
			 pwm=0;			
			 break;
			}
      tingzhi(); 		
		}			
	}	
}



 
