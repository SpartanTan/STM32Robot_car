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
#include "rgb3.h"
#include "movements.h"
#include "ceju.h"


//#define night

extern unsigned long pwm,pwmup;
extern int time,yanse,yansexuan;
extern u8 key;
extern u16 adcx;
extern int duan;
//����·��Ҫ�ܿ�

int biaozhi=0;

void ceyanse(void)
{
//	xiaoduoji(1);
//	while(1)
//	{

//		key = Remote_Scan();
//		
//		if(yanse==1)
//		{
//				led(0);
//				delay_ms(300);
//				led(2);
//				delay_ms(300);
//				led(0);
//				delay_ms(300);
//				led(2);
//				delay_ms(300);
//				led(0);
//		}
//		if(key==1)
//		{
//				led(0);
//				delay_ms(1000);
//				led(2);
//				delay_ms(1000);
//				led(0);
//				delay_ms(1000);
//				led(2);
//				delay_ms(1000);
//				led(0);
//		}
//		if(key==152)//2
//		{
//			if(biaozhi==1)
//			{
//				led(1);
//				delay_ms(1000);
//				led(2);
//				delay_ms(1000);
//			}
//			xiaoduoji(2);//����
//			delay_ms(2000);
//			whitebalance();
			duqui();//����ɫ
			
			if(Ramount<0x60)//��
			{
				yanse=1;
				led(0);
//				xiaoduoji(1);
				//ting();
				//break;
			}
			else if(Ramount<0xC0&&Ramount>0x60)//��
			{
				yanse=2;
				led(1);	
//				xiaoduoji(1);				
				//break;				
			}	
			else if(Ramount>0xC0)//��
			{
				yanse=3;
				led(2);
//				xiaoduoji(1);
				//break;
			}
//			ting();			
//		}
//	}
}
void xuanyanse(void)//ѡ��ɫ �ŵ�λ->ѡ->����
{	
	xiaoduoji(1);
	duoji1234(147,150,120,83);
	delay_ms(1000);
	delay_ms(1000);
	xiaoduoji(2);
	delay_ms(1000);
	delay_ms(1000);
	ceyanse();
	yansexuan=yanse;
	if(yansexuan==1)//��ɫ
	{
		led(0);
		delay_ms(1000);
		led(2);
		delay_ms(1000);
		led(0);
		delay_ms(1000);
		led(2);
		delay_ms(1000);
	}
	else if(yansexuan==2)//��ɫ
	{
		led(1);
		delay_ms(1000);
		led(2);
		delay_ms(1000);
		led(1);
		delay_ms(1000);
		led(2);
		delay_ms(1000);
	}
	else if(yansexuan==3)//��ɫ
	{
	  led(2);
		delay_ms(1000);
		led(2);
		delay_ms(1000);
		led(2);
		delay_ms(1000);
		led(2);
		delay_ms(1000);
	}
	xiaoduoji(1);
	delay_ms(1000);
	xiaoduoji(2);
	duoji1234kuai(147,66,112,74);//����
//	xiaoduoji(2);
}
void zhuawuliao()//ץ���ϣ���������->ץ��->����
{
	
//	delay_ms(500);
	while(1)
	{
		xiaoduoji(1);
		duoji1234kuai(147,145,212,116);//��������	
			delay_ms(300);
//			delay_ms(1000);
		mantiao(165,210,104);//��������
//			delay_ms(1000);
//			delay_ms(1000);
		xiaoduoji(2);//����
		ceyanse();//����ɫ
		if(yanse==yansexuan)//ƥ��
		{
			mantiao(145,212,118);//ץ��
			break;
		}
		else
		{
			xiaoduoji(1);//�ɿ�
			mantiao(145,212,118);//̧��
//			delay_ms(1000);
//			delay_ms(1000);
		}
		
		mantiao(128,234,102);//�ڶ�����
//			delay_ms(500);
//			delay_ms(1000);
		mantiao(158,232,86);//�ڶ�����
//			delay_ms(1000);
//			delay_ms(1000);
		xiaoduoji(2);//����
		ceyanse();//����ɫ
		if(yanse==yansexuan)//ƥ��
		{
			mantiao(128,234,102);//ץ��
			break;
		}
		else
		{
			xiaoduoji(1);//�ɿ�
			mantiao(128,234,102);//̧��
//				delay_ms(1000);
//				delay_ms(1000);
		}
		
		mantiao(116,250,100);//��һ����116,250,95 
//			delay_ms(1000);
//			delay_ms(1000);
			
		mantiao(156,249,74);//��һ����
//			delay_ms(1000);
//			delay_ms(1000);
		xiaoduoji(2);//����
		ceyanse();//����ɫ
		if(yanse==yansexuan)//ƥ��
		{
			mantiao(116,250,100);//ץ��
			delay_ms(300);
//			delay_ms(1000);
			break;
		}
		else
		{
			xiaoduoji(1);//�ɿ�
			mantiao(116,250,100);//̧��
				delay_ms(1000);
//				delay_ms(1000);
		}
			duoji1234kuai(147,120,160,74);
//			delay_ms(500);
	}
	duoji1342(147,66,112,74);
//	delay_ms(1000);
}
void feixunxian(void)//��Ѳ����
{
	pwmup=300;//200
	rukou1time(500);
	zhuanxiang(250,200,550);
	duanting(300);
	yuandiyouzhuanrukou0(200,200);//��ת
	
	while(1)//ֱ��ֱ��ײǽ
	{
		rukouzhixian();
		if(bizhangyou==0)
		{
			break;
		}
	}
	duanting(300);
	yuandizuozhuanrukou1(200,200);//��ת
	duanting(300);
	
	while(1)//ֱ��ֱ������ǽ
	{
		rukouzhixian();
		if(bizhangyou==0)
		{
			break;
		}
	}
	yuandizuozhuanrukou1(200,200);//��ת
	duanting(300);
	while(1)
	{
		rukouzhixian();
		if(chukou==1)
		{
			break;
		}
	}
//	ting();
	yuandiyouzhuan(200,200);
	delay_ms(500);
	yuandiyouzhuanbizhangyou0(200,200);//ԭ����תֱ����������
	zhuanxiang(200,220,300);
//	yuandiyouzhuanrukou0(200,200);
//	ting();
}
void feixunxian1(void)//��Ѳ����1//��
{
	led(1);
	rukou1time(400);//400
//	ting();
//	delay_ms(500);
//	zhuanxiang(300,280,50);
//	ting();
	
	while(1)
	{
		ceju();
		if(rukou==0)
		{
//			zhuanxiang(300,200,100);
//			ting();
			break;
		}
	}
//	if(bizhangyou==0)
//	{
//		zhuanxiang(300,400,100);
//	}
//	else if(bizhangzuo==0)
//	{
//		zhuanxiang(400,300,100);
//	}
	led(1);
}
void fangwuliao(void)//������
{
	if(yansexuan==1)//��
	{
		duoji1234(190,146,188,144);//158
		delay_ms(300);
		xiaoduoji(1);
//		delay_ms(1000);
		mantiao(120,186,130);//Ҫ��
//		delay_ms(1000);
		xiaoduoji(2);		
//		delay_ms(1000);		
	}
	else if(yansexuan==2)//��
	{
		duoji1234(147,146,188,144);
		delay_ms(300);
		xiaoduoji(1);
//		delay_ms(1000);
		mantiao(120,186,130);//Ҫ��
//		delay_ms(1000);
		xiaoduoji(2);		
//		delay_ms(1000);
	}
	else if(yansexuan==3)//��
	{
		duoji1234(110,146,188,136);
		delay_ms(300);
		xiaoduoji(1);
//		delay_ms(300);
		mantiao(120,186,130);//Ҫ��
//		delay_ms(1000);
		xiaoduoji(2);		
//		delay_ms(1000);
	}
	duoji3412kuai(147,66,112,74);
}
void zero(void)//����������ɽ//��
{
	#ifdef night
	led(2);
	#else
	led(1);
	#endif
	
	pwmup=400;
	jiasu4(pwmup);
	yunsu(pwmup,260);
	jiansu3(300);
	pwmup=300;
	while(1)
	{
		xunji();
		time++;
		if(zhangai == 1&&time>100)
		{
			time=0;
			duan = 1;
			break;
		}
	}
}
void one(void)//��������ɽ
{
	pwmup=300;//250
	while(1)
	{
//		ting();
		xunji();
		time++;
		if(time > 400)//400
		{
//			ting();//���Լ�ʱ��1000����λ��
			if(sebiaoyou == 0)
			{
//				ting();
				pwmup=300;
				time = 0;
				break;
			}
		}
	}
	while(1)
	{
		xunji();
		time++;
		if(time>350)
		{
//			ting();
			if(zhangai==1)
			{
//				ting();
//				led(1);
				time=0;
				duan=2;
				break;
			}
		}
	}
}

void two(void)//�����ٴ�����//�ĵ�
{
	pwmup=250;
	#ifdef night
	led(1);
	#else
	led(0);
	#endif
//	sebiaoyou0time(1200);
//	ting();
//	jiasudao(300);
//	pwmup=300;
//	sebiaoyou0time(20);
//	cgchasu(400,50);
//	ting();
	sebiaozuo0time(800);
//	ting();
	cgchasu(50,400);
	jiasudao(400);
	zhongjianyou0time(0);	
	sebiaoyou0time(100);
	cgchasu(400,50);
	pwmup=300;
//	while(1)//���ٴ���ת��
//	{
//		xunji();
//		time++;
//		if(time > 850)
//		{
////			ting();//���Լ�ʱ��800����λ�ã�Ӧ���ڼ��ٴ�֮��
//			if(sebiaozuo == 0)//���ٴ�֮����ת
//			{
////				ting();
//				cgchasu(50,400);//75 350
//				time=0;
//				break;
//			}
//		}
//	}
//				ting();
//	while(1)//��ǰת��
//	{
//		xunji();
//		time++;
//		if(time>420&&sebiaoyou==0)
//		{
////			zhuanxiang(400,50,30);
//			cgchasu(400,50);//��ת350 75
////			ting();
//			break;
////						ting();
//		}
//	}
	while(1)//ɨ��
	{
		xunji();
		time++;
		if(time>10&&zhangai == 1)//800
		{
//			ting();
			time = 0;
			duan = 3;
			break;
		}
	}
}

void three(void)//�������ŵ��Թ�ǰ//�ĵ�
{
//	zhuanxiang(380,260,150);
	pwmup=250;
	sebiaozuoyou0time(420);
//	ting();
//	zhangai0time(350);//������·��ǰ
////	ting();
//	sebiaoyou0time(0);
////	jiansu3(100);
////	ting();
//	pwmup=200;//����100
////	zhongjianzuo0time(300);
////	ting();
//	time=0;
//	zhongjianzuo1time(10);
//	while(1)
//	{
////		ting();
//		xunji();
//		time++;
//		if(time > 5)
//		{
////			ting();//���Լ�ʱ��500����λ��
//			if(sebiaozuo == 0||sebiaoyou==0)//||time > 200)//����Ҫ����time200�����ʹtimeת�価��������Ϊ����
//			{
////				ting();
//				break;
//			}
//		}
//	}
//	ting();
	pwmup=100;
	zhongjianzuo0time(100);//�ȴ��м�����,������øĳ���ʱ˫����
//	ting();
//	cgzhijiaozuo(300,300);//��ת
	duanting(150);
	zhijiaozuo(300,300,350);//ֱ����ת
//	duanting(150);
	jiasu3(300);
//	ting();//����ֱ����Ч��
	time=0;
	pwmup=300;//�ָ�ԭ��
	sebiaozuo0time(300);//��ʱ��ɨɫ����
	jiansu3(100);
	pwmup=100;
//	ting();
	zhongjianzuo0time(20);//�ȴ��м����ٴμ��
	duanting(150);
//	ting();//
	cgzhijiaozuo(300,300);//�ٴ���ת
//	zhijiaozuo(300,300,400);//ֱ����ת
	#ifdef night
	led(1);
	#else
	led(0);
	#endif
//	duanting(150);
//	ting();
	jiasudao(300);
	zhangai0time(0);
	yunsu(300,320);
	jiasudao(450);
	yunsu(450,270);
	jiansudao(300);
//	jiansudao(100);
//	ting();
//	ting();
//	yunsu(450,
	rukou0time(0);
	led(0);//��ֹ���ڸ���
	duan=4;
	time=0;
}
void four(void)//�Թ�
{
//	rukou0time(100);//ֻ���Թ���ʱ��ȥ��ע��
	chasubizhangyou0(400,200);//��תֱ��������ɨ����ǽ
//	ting();
	chasubizhangyou1(200,500);//��תֱ����������
//	ting();
	chasusebiaoyou0(180,230);//ֱ��ֱ��ɫ����ɨ������ǽ
	
	duanting(150);//��ͣ300
	
	yuandizuozhuansebiaoyou1(300,300);//ԭ����תֱ��ɫ������
	delay_ms(50);
//	ting();
	duanting(150);
//	chasusebiaoyou0(200,150);//ֱ��ֱ��ɫ����ɨ����ǽ
	chasusebiaozuo0(155,150);//ֱ��ֱ��ɫ����ɨ����ǽ//170 150
	duanting(150);
	yuandiyouzhuanbizhangzuo1(300,300);//ԭ����תֱ����������
	duanting(150);
//	ting();
	//����һ������ֱ��ת��
	chasusebiaoyou0(200,200);//ֱ��ֱ��ɫ����ɨ����ǽ
	duanting(150);//��ͣ300

	zhijiaoyou(300,300,100);
	yuandiyouzhuanbizhangzuo1(300,300);//ԭ����תֱ����������
//	zhijiaoyou(300,300,100);
	duanting(150);
//		ting();
	chasusebiaoyou0(200,200);//ֱ��ֱ��ɫ����ɨ����ǽ
	zhuanxiang(200,200,50);
//	ting();
	duanting(150);
	yuandizuozhuanbizhangyou1(300,300);//ԭ����תֱ����������
	duanting(150);//��ͣ300
//	ting();
	chasurukou1(120,220);//����ֱ�������
//	zhuanxiang(150,100,100);
	jiasudao(300);//���ٵ�300
//	ting();
//	yunsu(200,500);
	duan=5;
//	ting();
}
void four1(void)//�Թ�1
{
	rukou0time(100);//ֻ���Թ���ʱ��ȥ��ע��
	chasubizhangyou0(400,200);//��תֱ��������ɨ����ǽ
	bzylinesebiaoyou0();//������Ѱֱ��ֱ��ɫ����0
	ting();
}
void five(void)//���Թ�������ǰ//��
{
	#ifdef night
	led(2);
	#else
	led(1);
	#endif
	yunsu(300,50);
	jiasudao(450);
	zhangai0time(50);
	yunsu(400,300);
//	jiansudao(350);
//	yunsu(350,500);
	jiansudao(300);
//	sebiaoyou0time(1300);//�����²�ֱ��1
	sebiaoyou0time(10);//�����²�ֱ��1
//	ting();
	jiansudao(100);//���ٵ�100
	zhongjianyou0time(10);//�м���ɨ��ֱ��1
	duanting(150);//��ͣ
	cgzhijiaoyou(300,300);//����ֱ����
	delay_ms(50);
//	duanting(150);
	jiasudao(200);//���ٵ�200
	sebiaoyou0time(10);//ɫ����ɨ��ֱ��2
	jiansudao(100);//���ٵ�100
	zhongjianyou0time(0);//�м���ɨ��ֱ��2
	duanting(150);//��ͣ
	zhijiaoyou(300,300,150);
	cgzhijiaoyou(300,300);//����ֱ����
	yunsu(100,500);//��ǰ��һС��
//	duanting(300);//��ͣ
//	ting();
	daochesebiaohou0();//����ɫ�괥��
	daochesebiaohou1();
//	daoche(100,100);//�ܹ�����
//	delay_ms(500);
	daochesebiaohou0();//����ɫ�괥��
	speed1(0,0);
//	ting();
	duan=6;
	time=0;

}
void six(void)//ȡ���ϵ���Ѳ����ǰ
{
	zhuawuliao();//ץ����
//	duoji1234(120,250,95);
//	ting();
	#ifdef night
	led(2);
	#else
	led(0);
	#endif
	zhongjianzuo0time(50);//�м�����
	duanting(150);//��ͣ
//	zhijiaozuo(300,300,70);
	cgzhijiaozuo(300,300);//����ֱ����ת
	duanting(150);//��ͣ
	jiasudao(300);//���ٵ�300
//	sebiaoyou0time(0);//�ܹ�������·
//	delay_ms(50);
//	sebiaoyou0time(0);
//	delay_ms(50);
	sebiaoyou0time(250);//ɫ���Ҵ���//250
	jiansudao(100);//���ٵ�100
	zhongjianyou0time(0);//�м��Ҵ���
	duanting(150);//��ͣ
//	zhijiaoyou(300,300,200);
	cgzhijiaoyou(300,300);//����ֱ����ת
	duanting(150);//��ͣ
	jiasudao(400);//���ٵ�300
	zhangai1time(100);//ɨ�ϰ�
//	jiansudao(300);
//	yunsu(300,300);
//	jiasudao(400);
//	ting();
	time=0;
	duan=7;
}
void seven(void)//��Ѳ����
{
//	jiasudao(400);//���ٵ�300
//	zhangai1time(100);//ɨ�ϰ�
	led(0);
	feixunxian1();
//	ting();
	duan=8;

}
void eight(void)//����Ѳ������ͣ�ڻ�ջǰ//��
{
//	jiasudao(300);//
	zhangai0time(0);
	zhangai1time(50);
	jiasudao(450);
	yunsu(450,250);
	jiansudao(350);
	time=0;
	led(1);
	sebiaoyou0time(0);//ɨֱ��
	jiansudao(100);//���ٵ�100
	zhongjianyou0time(0);//ɨ�м���
	duanting(150);
	cgzhijiaoyou(300,300);//����ֱ����ת
	duanting(150);
	jiasudao(450);//���ٵ�300
	sebiaoyou0time(0);//ɨ��һ����·
	delay_ms(50);
	sebiaoyou0time(0);//ɨ�ڶ�����·
	delay_ms(50);
	zhangai1time(0);//ɨ�ϰ�
	jiansudao(350);
	sebiaozuo0time(130);//ɨ��ջ·��
	jiansudao(100);//���ٵ�100
	zhongjianzuo0time(0);//�м���ɨ·��
	duanting(200);
	zhijiaoyou(300,300,420);
//	ting();
//	cgzhijiaoyou(300,300);//ֱ����ת
//	duanting(300);
	daoche(150,150);
	delay_ms(300);
	daochesebiaohou0();//����ɨ��ɫ��
	speed1(0,0);
//	duanting(300);
//	ting();
	duan=9;
}
void nine(void)//�����ϵ�ʮ��·��
{
//	daochesebiaohou0();//ȫ��ʱɾ��
//	speed1(0,0);
	fangwuliao();//������
//	ting();
	pwmup=200;
	zhongjianzuo0time(0);//�м���ɨ��
	duanting(150);
	cgzhijiaozuo(300,300);//����ֱ����ת
	duanting(150);
//	jiasudao(300);//���ٵ�200
	zhongjianyou0time(0);//�м���ɨ��
	duanting(150);
	cgzhijiaoyou(300,300);//����ֱ����ת
//	duanting(150);
	zhangai1time(0);//ɨ��
	led(0);
//	yunsu(300,350);
	jiasudao(300);
	yunsu(300,480);
	#ifdef night
	led(2);
	#else
	led(1);
	#endif
//	ting();
	jiasudao(400);
//	sebiaoyou0time(250);//ɨ��ʮ��·
//	jiansudao(100);
//	ting();
//	ting();
	duan=10;
}
void ten(void)//ʮ��·�ڵ�������//��
{
	zhangai1time(100);
//	jiansudao(100);
//	ting();
	jiansudao(250);
//	ting();
	zhangai1time(550);
	jiasudao(300);
	zhangai0time(300);
//	ting();
	jiansudao(200);
	yunsu(200,450);//��������
	jiasudao(300);
//	ting();
	duan=11;
}
void eleven(void)//��������
{
	zhangai1time(300);
//	yunsu(300,300);
	jiasudao(400);
//	ting();
	sebiaoyou0time(240);//800
//	ting();
	jiansudao(300);
	yunsu(300,100);
	jiansu3(100);
	ting();
}
void twelve(void);
void thirteen(void);
void fourteen(void);
void fifteen(void);



