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
void yunsu(long a,long b)//�ٶ� ʱ�䣨ѭ��)
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

void duanting(u16 time)//��ͣ
{
	tingzhi();
	delay_ms(time);
}
void ting(void)//����ֹͣ
{
	while(1)
	{
		tingzhi();
	}
}
void jiansu3(long a)//����3��>a
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
void jiansu4(long a)//����4��>a
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
void jiansu5(long a)//����5��>a
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
void jiasu3(long a)//����3��>a
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
void jiasu2(long a)//����2��>a
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
void jiasu4(long a)//����4��>a
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
void jiansusmall(long a)//΢���١�>a
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
void jiasudao(u16 speed)//���ٵ�speed
{
	jiasu3(speed);
	pwmup=speed;
}
void jiansudao(u16 speed)//���ٵ�speed
{
	jiansu3(speed);
	pwmup=speed;
}
void zhijiaozuo(u16 zuo,u16 you,u16 time)//��ʱֱ����ת
{
	yuandizuozhuan(zuo,you);
	delay_ms(time);//���ԭ��ת
}
void zhijiaoyou(u16 zuo,u16 you,u16 time)//��ʱֱ����ת
{
	yuandiyouzhuan(zuo,you);
	delay_ms(time);//���ԭ��ת
}
void zhuanxiang(u16 zuo,u16 you,u16 time)//ת����ʱ��
{
	zhuanwan(zuo,you);
	delay_ms(time);//�����ת
}
void daochexunxian()//����Ѳ��
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
void cgzhijiaozuo(u16 zuo,u16 you)//������ֱ����ת
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
void cgzhijiaoyou(u16 zuo, u16 you)//������ֱ����ת
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
void cgchasu(u16 zuo,u16 you)//����������
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
void zhangai0time(u16 time_set)//��ʱ��ɨ��̺
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
void zhangai1time(u16 time_set)//��ʱ��ɨ�ϰ�
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
void zhongjianzuo0time(u16 time_set)//��ʱ��ɨ�м���
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
void zhongjianzuo1time(u16 time_set)//��ʱ��ɨ�м�����
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
void zhongjianyou0time(u16 time_set)//��ʱ��ɨ�м���
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
void rukou0time(u16 time_set)//��ʱ��ɨ�Թ����
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
void rukou1time(u16 time_set)//����Ѳ�������
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
void sebiaozuo0time(u16 time_set)//��ʱ��ɨɫ����
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
void daochesebiaohou0(void)//Ѳ�ߵ�����ʱ��ɨɫ���
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
void daochesebiaohou1(void)//Ѳ�ߵ���ɫ����
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
void sebiaoyou0time(u16 time_set)//��ʱ��ɨɫ����
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
void sebiaozuoyou0time(u16 time_set)//��ʱ��ɨɫ������
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
void chasusebiaoyou0(u16 zuo,u16 you)//����ֱ��ɫ����ɨ����ǽ
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
void chasusebiaozuo0(u16 zuo,u16 you)//����ֱ��ɫ����ɨ����ǽ
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
void yuandizuozhuansebiaoyou1(u16 zuo,u16 you)//ԭ����תֱ��ɫ������
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

void yuandiyouzhuanbizhangzuo1(u16 zuo,u16 you)//ԭ����תֱ����������
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
void yuandizuozhuanbizhangyou1(u16 zuo,u16 you)//ԭ����תֱ����������
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
void yuandiyouzhuanbizhangyou0(u16 zuo,u16 you)//ԭ����תֱ����������
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
void chasubizhangyou0(u16 zuo,u16 you)//����ֱ��������ɨ����ǽ
{
	while(1)
	{
		zhuanwan(zuo,you);//ɨ���������ת
		delay_ms(30);
		if(bizhangyou==0)
		{
//			ting();
			 break;
		}
	}
}
void chasubizhangyou1(u16 zuo,u16 you)//����ֱ����������
{
	while(1)
	{
		zhuanwan(zuo,you);//ɨ���������ת
		delay_ms(30);
		if(bizhangyou==1)
		{
//			ting();
			 break;
		}
	}
}
void chasubizhangzuo0(u16 zuo,u16 you)//����ֱ��������ɨ����ǽ
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
void chasurukou1(u16 zuo,u16 you)//����ֱ�������
{
	while(1)
	{
		zhuanwan(zuo,you);//ɨ���������ת
		delay_ms(30);
		if(rukou==1)
		{
//			ting();
			 break;
		}
	}
}
void rukouzhixian(void)//����ڴ�������ֱ��
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
void yuandiyouzhuanrukou0(u16 zuo,u16 you)//ԭ����תֱ��ɨ�����
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
void yuandizuozhuanrukou1(u16 zuo,u16 you)//ԭ����תֱ�������
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
void chasurukou0(u16 zuo,u16 you)//����ֱ�����ɨ����ǽ
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
void bizhangyouzhixian(void)//�ñ�������ֱ��
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
void bzylinesebiaoyou0(void)//������ֱ��ֱ��ɫ����0
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
