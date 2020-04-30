#include "fenduan.h"
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
#include "movements.h"

extern unsigned long pwm,pwmup;
extern int time;
void led(int a)
{
	if(a==1)
	{
		LED1_ON;
		LED2_OFF;
//		LED3_OFF;
	}
	else if(a==2)
	{
		LED1_ON;
		LED2_ON;
//		LED3_OFF;
//		LED1_ON;
	}
	else if(a==0)
	{
		LED1_OFF;
		LED2_OFF;
	}
}
void yunsu(long a,long b)//速度 时间（循迹)
{
	while(1)
	{
		if(pwm>a)
		{
			pwm=a;
		}
		xunji();
		time++;
		if(time>b)
		{
			time=0;
			break;
		}
	}
}

void duanting(u16 time)//短停
{
	tingzhi();
	delay_ms(time);
}
void ting(void)//立刻停止
{
	while(1)
	{
		tingzhi();
	}
}
void jiansu3(long a)//减速3—>a
{
	while(1)
	{
		xunji1();
		pwm=pwm-3;
		if(pwm<a)
		{
			break;
		}
	}
}
void jiansu4(long a)//减速4—>a
{
	while(1)
	{
		xunji1();
		pwm=pwm-4;
		if(pwm<a)
		{
			break;
		}
	}
}
void jiansu5(long a)//减速5—>a
{
	while(1)
	{
		xunji1();
		pwm=pwm-5;
		if(pwm<a)
		{
			break;
		}
	}
}
void jiasu3(long a)//加速3—>a
{
	while(1)
	{
		xunji1();
		pwm=pwm+3;
		if(pwm>a)
		{
			break;
		}
	}
}
void jiasu2(long a)//加速2—>a
{
	while(1)
	{
		xunji1();
		pwm=pwm+2;
		if(pwm>a)
		{
			break;
		}
	}
}
void jiasu4(long a)//加速4—>a
{
	while(1)
	{
		xunji1();
		pwm=pwm+4;
		if(pwm>a)
		{
			break;
		}
	}
}
void jiansusmall(long a)//微减速—>a
{
	while(1)
	{
		xunji1();
		time++;
		if(time%2==0)
			pwm=pwm-1;
		if(pwm<a)
		{
			break;
		}
	}
}
void jiasudao(u16 speed)//加速到speed
{
	jiasu3(speed);
	pwmup=speed;
}
void jiansudao(u16 speed)//减速到speed
{
	jiansu3(speed);
	pwmup=speed;
}
void zhijiaozuo(u16 zuo,u16 you,u16 time)//延时直角左转
{
	yuandizuozhuan(zuo,you);
	delay_ms(time);//完成原地转
}
void zhijiaoyou(u16 zuo,u16 you,u16 time)//延时直角右转
{
	yuandiyouzhuan(zuo,you);
	delay_ms(time);//完成原地转
}
void zhuanxiang(u16 zuo,u16 you,u16 time)//转向（延时）
{
	zhuanwan(zuo,you);
	delay_ms(time);//完成右转
}
void daochexunxian()//倒车巡线
{
	if(huiduyou==0&&huiduzuo==1)
		{
			daoche(100,0);
//			delay_ms(100);
		}
		else if(huiduyou==1&&huiduzuo==0)
		{
			daoche(0,100);
//			delay_ms(100);
		}
		else if(huiduyou==0&&huiduzuo==0)
		{
//			ting();
			daoche(100,100);
//			delay_ms(100);
		}
		else
		{
			daoche(100,100);
//			delay_ms(100);
		}
}
void cgzhijiaozuo(u16 zuo,u16 you)//传感器直角左转
{
	yuandizuozhuan(zuo,you);
	delay_ms(150);
	while(1)
	{
		yuandizuozhuan(zuo,you);
		if(sebiaoqian==0)
		{
			break;
		}
	}
}
void cgzhijiaoyou(u16 zuo, u16 you)//传感器直角右转
{
	yuandiyouzhuan(zuo,you);
	delay_ms(150);
		while(1)
	{
		yuandiyouzhuan(zuo,you);
		if(sebiaoqian==0)
		{
			break;
		}
	}
}
void cgchasu(u16 zuo,u16 you)//传感器差速
{
	zhuanwan(zuo,you);
	delay_ms(100);
	while(1)
	{
		zhuanwan(zuo,you);
		if(sebiaoqian==0)
		{
			break;
		}
	}
}
void zhangai0time(u16 time_set)//过时间扫地毯
{
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(zhangai==0)
			{
				time=0;
				break;
			}		
		}
	}
}
void zhangai1time(u16 time_set)//过时间扫障碍
{
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(zhangai==1)
			{
				time=0;
				break;
			}		
		}
	}
}
void zhongjianzuo0time(u16 time_set)//过时间扫中间左
{
//	ting();
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(zhongjianzuo==0)
			{
				time=0;
				break;
			}		
		}
	}
}
void zhongjianzuo1time(u16 time_set)//过时间扫中间左灭
{
//	ting();
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(zhongjianzuo==1)
			{
				time=0;
				break;
			}		
		}
	}
}
void zhongjianyou0time(u16 time_set)//过时间扫中间左
{
//	ting();
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(zhongjianyou==0)
			{
				time=0;
				break;
			}		
		}
	}
}
void rukou0time(u16 time_set)//过时间扫迷宫入口
{
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(rukou==0)
			{
				time=0;
				break;
			}		
		}
	}
}
void rukou1time(u16 time_set)//过非巡线区入口
{
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(rukou==1)
			{
				time=0;
				break;
			}		
		}
	}
}
void sebiaozuo0time(u16 time_set)//过时间扫色标左
{
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(sebiaozuo==0)
			{
				time=0;
				break;
			}		
		}
	}
}
void daochesebiaohou0(void)//巡线倒车过时间扫色标后
{
	time=0;
	while(1)
	{
		daochexunxian();
		if(sebiaohou==0)
		{
			break;
		}
	}
}
void daochesebiaohou1(void)//巡线倒车色标灭
{
	time=0;
	while(1)
	{
		daochexunxian();
		if(sebiaohou==1)
		{
			break;
		}
	}
}
void sebiaoyou0time(u16 time_set)//过时间扫色标右
{
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(sebiaoyou==0)
			{
				time=0;
				break;
			}		
		}
	}
}
void sebiaozuoyou0time(u16 time_set)//过时间扫色标左右
{
	time=0;
	while(1)
	{
		xunji();
		time++;
		if(time>time_set)
		{
			if(sebiaoyou==0||sebiaozuo==0)
			{
				time=0;
				break;
			}		
		}
	}
}
void chasusebiaoyou0(u16 zuo,u16 you)//差速直到色标右扫到正墙
{
	while(1)
	{
		zhuanwan(zuo,you);
		delay_ms(30);
		if(sebiaoyou==0)
		{
//			ting();
			break;
		}
	}
}
void chasusebiaozuo0(u16 zuo,u16 you)//差速直到色标左扫到正墙
{
	while(1)
	{
		zhuanwan(zuo,you);
		delay_ms(30);
		if(sebiaoyou==0)
		{
//			ting();
			break;
		}
	}
}
void yuandizuozhuansebiaoyou1(u16 zuo,u16 you)//原地左转直到色标右灭
{
	while(1)
	{
		yuandizuozhuan(zuo,you);
		delay_ms(30);
		if(sebiaoyou==1)
		{
			pwm=0;
//			ting();
			break;
		}
	}
}

void yuandiyouzhuanbizhangzuo1(u16 zuo,u16 you)//原地右转直到避障左灭
{
	while(1)
	{
		yuandiyouzhuan(zuo,you);
		delay_ms(30);
		if(bizhangzuo==1)
		{
			pwm=0;
//			ting();
			break;
		}
	}
}
void yuandizuozhuanbizhangyou1(u16 zuo,u16 you)//原地左转直到避障右灭
{
	while(1)
	{
		yuandizuozhuan(zuo,you);
		delay_ms(30);
		if(bizhangyou==1)
		{
			pwm=0;
//			ting();
			break;
		}
	}
}
void yuandiyouzhuanbizhangyou0(u16 zuo,u16 you)//原地左转直到避障右亮
{
	while(1)
	{
		yuandiyouzhuan(zuo,you);
		delay_ms(30);
		if(bizhangyou==0)
		{
			pwm=0;
//			ting();
			break;
		}
	}
}
void chasubizhangyou0(u16 zuo,u16 you)//差速直到避障右扫到侧墙
{
	while(1)
	{
		zhuanwan(zuo,you);//扫到入入口右转
		delay_ms(30);
		if(bizhangyou==0)
		{
//			ting();
			 break;
		}
	}
}
void chasubizhangyou1(u16 zuo,u16 you)//差速直到避障右灭
{
	while(1)
	{
		zhuanwan(zuo,you);//扫到入入口右转
		delay_ms(30);
		if(bizhangyou==1)
		{
//			ting();
			 break;
		}
	}
}
void chasubizhangzuo0(u16 zuo,u16 you)//差速直到避障左扫到正墙
{
	while(1)
	{
		zhuanwan(zuo,you);
		delay_ms(30);
		if(bizhangzuo==0)
		{
//			ting();
			break;
		}
	}
}
void chasurukou1(u16 zuo,u16 you)//差速直到入口灭
{
	while(1)
	{
		zhuanwan(zuo,you);//扫到入入口右转
		delay_ms(30);
		if(rukou==1)
		{
//			ting();
			 break;
		}
	}
}
void rukouzhixian(void)//用入口传感器走直线
{
	if(rukou==0)
	{
		zhuanwan(100,150);
		delay_ms(30);
	}
	else
	{
		zhuanwan(150,100);
		delay_ms(30);
	}
}
void yuandiyouzhuanrukou0(u16 zuo,u16 you)//原地右转直到扫到入口
{
	while(1)
	{
		yuandiyouzhuan(zuo,you);
		delay_ms(30);
		if(rukou==0)
		{
//			ting();
			pwm=0;
			break;
		}
	}
}
void yuandizuozhuanrukou1(u16 zuo,u16 you)//原地左转直到入口灭
{
		yuandizuozhuan(zuo,you);
		delay_ms(300);
	
	while(1)
	{
		yuandizuozhuan(zuo,you);
		delay_ms(30);
		if(rukou==1)
		{
			pwm=0;
//			ting();
			break;
		}
	}
}
void chasurukou0(u16 zuo,u16 you)//差速直到入口扫到侧墙
{
	while(1)
	{
		zhuanwan(zuo,you);
		delay_ms(30);
		if(rukou==0)
		{
//			ting();
			break;
		}
	}
}
void bizhangyouzhixian(void)//用避障右走直线
{
	if(bizhangyou==0)
	{
		zhuanwan(100,150);
		delay_ms(30);
	}
	else
	{
		zhuanwan(150,100);
		delay_ms(30);
	}
}
void bzylinesebiaoyou0(void)//避障右直线直到色标右0
{
	while(1)
	{
		bizhangyouzhixian();
		if(sebiaoyou==0)
		{
//			ting();
			break;
		}
	}
}
