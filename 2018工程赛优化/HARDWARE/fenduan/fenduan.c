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
//交叉路口要避开

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
//			xiaoduoji(2);//卡紧
//			delay_ms(2000);
//			whitebalance();
			duqui();//读颜色
			
			if(Ramount<0x60)//绿
			{
				yanse=1;
				led(0);
//				xiaoduoji(1);
				//ting();
				//break;
			}
			else if(Ramount<0xC0&&Ramount>0x60)//红
			{
				yanse=2;
				led(1);	
//				xiaoduoji(1);				
				//break;				
			}	
			else if(Ramount>0xC0)//白
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
void xuanyanse(void)//选颜色 放到位->选->收纳
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
	if(yansexuan==1)//绿色
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
	else if(yansexuan==2)//红色
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
	else if(yansexuan==3)//白色
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
	duoji1234kuai(147,66,112,74);//收纳
//	xiaoduoji(2);
}
void zhuawuliao()//抓物料：第三排上->抓起->收纳
{
	
//	delay_ms(500);
	while(1)
	{
		xiaoduoji(1);
		duoji1234kuai(147,145,212,116);//第三排上	
			delay_ms(300);
//			delay_ms(1000);
		mantiao(165,210,104);//第三排下
//			delay_ms(1000);
//			delay_ms(1000);
		xiaoduoji(2);//卡紧
		ceyanse();//测颜色
		if(yanse==yansexuan)//匹配
		{
			mantiao(145,212,118);//抓起
			break;
		}
		else
		{
			xiaoduoji(1);//松开
			mantiao(145,212,118);//抬起
//			delay_ms(1000);
//			delay_ms(1000);
		}
		
		mantiao(128,234,102);//第二排上
//			delay_ms(500);
//			delay_ms(1000);
		mantiao(158,232,86);//第二排下
//			delay_ms(1000);
//			delay_ms(1000);
		xiaoduoji(2);//卡紧
		ceyanse();//测颜色
		if(yanse==yansexuan)//匹配
		{
			mantiao(128,234,102);//抓起
			break;
		}
		else
		{
			xiaoduoji(1);//松开
			mantiao(128,234,102);//抬起
//				delay_ms(1000);
//				delay_ms(1000);
		}
		
		mantiao(116,250,100);//第一排上116,250,95 
//			delay_ms(1000);
//			delay_ms(1000);
			
		mantiao(156,249,74);//第一排下
//			delay_ms(1000);
//			delay_ms(1000);
		xiaoduoji(2);//卡紧
		ceyanse();//测颜色
		if(yanse==yansexuan)//匹配
		{
			mantiao(116,250,100);//抓起
			delay_ms(300);
//			delay_ms(1000);
			break;
		}
		else
		{
			xiaoduoji(1);//松开
			mantiao(116,250,100);//抬起
				delay_ms(1000);
//				delay_ms(1000);
		}
			duoji1234kuai(147,120,160,74);
//			delay_ms(500);
	}
	duoji1342(147,66,112,74);
//	delay_ms(1000);
}
void feixunxian(void)//非巡线区
{
	pwmup=300;//200
	rukou1time(500);
	zhuanxiang(250,200,550);
	duanting(300);
	yuandiyouzhuanrukou0(200,200);//右转
	
	while(1)//直行直到撞墙
	{
		rukouzhixian();
		if(bizhangyou==0)
		{
			break;
		}
	}
	duanting(300);
	yuandizuozhuanrukou1(200,200);//左转
	duanting(300);
	
	while(1)//直行直到对面墙
	{
		rukouzhixian();
		if(bizhangyou==0)
		{
			break;
		}
	}
	yuandizuozhuanrukou1(200,200);//左转
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
	yuandiyouzhuanbizhangyou0(200,200);//原地左转直到避障右亮
	zhuanxiang(200,220,300);
//	yuandiyouzhuanrukou0(200,200);
//	ting();
}
void feixunxian1(void)//非巡线区1//灯
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
void fangwuliao(void)//放物料
{
	if(yansexuan==1)//绿
	{
		duoji1234(190,146,188,144);//158
		delay_ms(300);
		xiaoduoji(1);
//		delay_ms(1000);
		mantiao(120,186,130);//要调
//		delay_ms(1000);
		xiaoduoji(2);		
//		delay_ms(1000);		
	}
	else if(yansexuan==2)//红
	{
		duoji1234(147,146,188,144);
		delay_ms(300);
		xiaoduoji(1);
//		delay_ms(1000);
		mantiao(120,186,130);//要调
//		delay_ms(1000);
		xiaoduoji(2);		
//		delay_ms(1000);
	}
	else if(yansexuan==3)//白
	{
		duoji1234(110,146,188,136);
		delay_ms(300);
		xiaoduoji(1);
//		delay_ms(300);
		mantiao(120,186,130);//要调
//		delay_ms(1000);
		xiaoduoji(2);		
//		delay_ms(1000);
	}
	duoji3412kuai(147,66,112,74);
}
void zero(void)//出发到梯形山//灯
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
void one(void)//上下梯形山
{
	pwmup=300;//250
	while(1)
	{
//		ting();
		xunji();
		time++;
		if(time > 400)//400
		{
//			ting();//测试计时点1000所处位置
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

void two(void)//过减速带到门//改灯
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
//	while(1)//减速带后转弯
//	{
//		xunji();
//		time++;
//		if(time > 850)
//		{
////			ting();//测试计时点800所处位置，应该在减速带之后
//			if(sebiaozuo == 0)//减速带之后左转
//			{
////				ting();
//				cgchasu(50,400);//75 350
//				time=0;
//				break;
//			}
//		}
//	}
//				ting();
//	while(1)//门前转弯
//	{
//		xunji();
//		time++;
//		if(time>420&&sebiaoyou==0)
//		{
////			zhuanxiang(400,50,30);
//			cgchasu(400,50);//右转350 75
////			ting();
//			break;
////						ting();
//		}
//	}
	while(1)//扫门
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

void three(void)//过两个门到迷宫前//改灯
{
//	zhuanxiang(380,260,150);
	pwmup=250;
	sebiaozuoyou0time(420);
//	ting();
//	zhangai0time(350);//到丁字路口前
////	ting();
//	sebiaoyou0time(0);
////	jiansu3(100);
////	ting();
//	pwmup=200;//减速100
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
////			ting();//测试计时点500所处位置
//			if(sebiaozuo == 0||sebiaoyou==0)//||time > 200)//这里要测试time200在哪里，使time转弯尽可能晚作为保底
//			{
////				ting();
//				break;
//			}
//		}
//	}
//	ting();
	pwmup=100;
	zhongjianzuo0time(100);//等待中间左检测,这里最好改成延时双保险
//	ting();
//	cgzhijiaozuo(300,300);//左转
	duanting(150);
	zhijiaozuo(300,300,350);//直角左转
//	duanting(150);
	jiasu3(300);
//	ting();//测试直角弯效果
	time=0;
	pwmup=300;//恢复原速
	sebiaozuo0time(300);//过时间扫色标左
	jiansu3(100);
	pwmup=100;
//	ting();
	zhongjianzuo0time(20);//等待中间左再次检测
	duanting(150);
//	ting();//
	cgzhijiaozuo(300,300);//再次左转
//	zhijiaozuo(300,300,400);//直角左转
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
	led(0);//防止门内干扰
	duan=4;
	time=0;
}
void four(void)//迷宫
{
//	rukou0time(100);//只调迷宫的时候去掉注释
	chasubizhangyou0(400,200);//右转直到避障右扫到侧墙
//	ting();
	chasubizhangyou1(200,500);//左转直到避障右灭
//	ting();
	chasusebiaoyou0(180,230);//直线直到色标右扫到正面墙
	
	duanting(150);//短停300
	
	yuandizuozhuansebiaoyou1(300,300);//原地左转直到色标右灭
	delay_ms(50);
//	ting();
	duanting(150);
//	chasusebiaoyou0(200,150);//直线直到色标右扫到侧墙
	chasusebiaozuo0(155,150);//直线直到色标左扫到侧墙//170 150
	duanting(150);
	yuandiyouzhuanbizhangzuo1(300,300);//原地右转直到避障左灭
	duanting(150);
//	ting();
	//方法一：依旧直角转弯
	chasusebiaoyou0(200,200);//直线直到色标右扫到正墙
	duanting(150);//短停300

	zhijiaoyou(300,300,100);
	yuandiyouzhuanbizhangzuo1(300,300);//原地右转直到避障左灭
//	zhijiaoyou(300,300,100);
	duanting(150);
//		ting();
	chasusebiaoyou0(200,200);//直线直到色标右扫到侧墙
	zhuanxiang(200,200,50);
//	ting();
	duanting(150);
	yuandizuozhuanbizhangyou1(300,300);//原地左转直到避障右灭
	duanting(150);//短停300
//	ting();
	chasurukou1(120,220);//差速直到入口灭
//	zhuanxiang(150,100,100);
	jiasudao(300);//加速到300
//	ting();
//	yunsu(200,500);
	duan=5;
//	ting();
}
void four1(void)//迷宫1
{
	rukou0time(100);//只调迷宫的时候去掉注释
	chasubizhangyou0(400,200);//右转直到避障右扫到侧墙
	bzylinesebiaoyou0();//避障右寻直线直到色标右0
	ting();
}
void five(void)//出迷宫到物料前//灯
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
//	sebiaoyou0time(1300);//过悬崖测直角1
	sebiaoyou0time(10);//过悬崖测直角1
//	ting();
	jiansudao(100);//减速到100
	zhongjianyou0time(10);//中间右扫到直角1
	duanting(150);//短停
	cgzhijiaoyou(300,300);//传感直角右
	delay_ms(50);
//	duanting(150);
	jiasudao(200);//加速到200
	sebiaoyou0time(10);//色标右扫到直角2
	jiansudao(100);//减速到100
	zhongjianyou0time(0);//中间右扫到直角2
	duanting(150);//短停
	zhijiaoyou(300,300,150);
	cgzhijiaoyou(300,300);//传感直角右
	yunsu(100,500);//向前开一小段
//	duanting(300);//短停
//	ting();
	daochesebiaohou0();//倒车色标触线
	daochesebiaohou1();
//	daoche(100,100);//避过白线
//	delay_ms(500);
	daochesebiaohou0();//倒车色标触线
	speed1(0,0);
//	ting();
	duan=6;
	time=0;

}
void six(void)//取物料到非巡线区前
{
	zhuawuliao();//抓物料
//	duoji1234(120,250,95);
//	ting();
	#ifdef night
	led(2);
	#else
	led(0);
	#endif
	zhongjianzuo0time(50);//中间左触线
	duanting(150);//短停
//	zhijiaozuo(300,300,70);
	cgzhijiaozuo(300,300);//传感直角左转
	duanting(150);//短停
	jiasudao(300);//加速到300
//	sebiaoyou0time(0);//避过两个岔路
//	delay_ms(50);
//	sebiaoyou0time(0);
//	delay_ms(50);
	sebiaoyou0time(250);//色标右触线//250
	jiansudao(100);//减速到100
	zhongjianyou0time(0);//中间右触线
	duanting(150);//短停
//	zhijiaoyou(300,300,200);
	cgzhijiaoyou(300,300);//传感直角右转
	duanting(150);//短停
	jiasudao(400);//加速到300
	zhangai1time(100);//扫障碍
//	jiansudao(300);
//	yunsu(300,300);
//	jiasudao(400);
//	ting();
	time=0;
	duan=7;
}
void seven(void)//非巡线区
{
//	jiasudao(400);//加速到300
//	zhangai1time(100);//扫障碍
	led(0);
	feixunxian1();
//	ting();
	duan=8;

}
void eight(void)//出非巡线区到停在货栈前//灯
{
//	jiasudao(300);//
	zhangai0time(0);
	zhangai1time(50);
	jiasudao(450);
	yunsu(450,250);
	jiansudao(350);
	time=0;
	led(1);
	sebiaoyou0time(0);//扫直角
	jiansudao(100);//减速到100
	zhongjianyou0time(0);//扫中间右
	duanting(150);
	cgzhijiaoyou(300,300);//传感直角右转
	duanting(150);
	jiasudao(450);//加速到300
	sebiaoyou0time(0);//扫第一个岔路
	delay_ms(50);
	sebiaoyou0time(0);//扫第二个岔路
	delay_ms(50);
	zhangai1time(0);//扫障碍
	jiansudao(350);
	sebiaozuo0time(130);//扫货栈路口
	jiansudao(100);//减速到100
	zhongjianzuo0time(0);//中间左扫路口
	duanting(200);
	zhijiaoyou(300,300,420);
//	ting();
//	cgzhijiaoyou(300,300);//直角右转
//	duanting(300);
	daoche(150,150);
	delay_ms(300);
	daochesebiaohou0();//倒车扫后色标
	speed1(0,0);
//	duanting(300);
//	ting();
	duan=9;
}
void nine(void)//放物料到十字路口
{
//	daochesebiaohou0();//全程时删除
//	speed1(0,0);
	fangwuliao();//放物料
//	ting();
	pwmup=200;
	zhongjianzuo0time(0);//中间左扫到
	duanting(150);
	cgzhijiaozuo(300,300);//传感直角左转
	duanting(150);
//	jiasudao(300);//加速到200
	zhongjianyou0time(0);//中间右扫到
	duanting(150);
	cgzhijiaoyou(300,300);//传感直角右转
//	duanting(150);
	zhangai1time(0);//扫门
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
//	sebiaoyou0time(250);//扫到十字路
//	jiansudao(100);
//	ting();
//	ting();
	duan=10;
}
void ten(void)//十字路口到单边桥//灯
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
	yunsu(200,450);//单边桥上
	jiasudao(300);
//	ting();
	duan=11;
}
void eleven(void)//过单边桥
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



