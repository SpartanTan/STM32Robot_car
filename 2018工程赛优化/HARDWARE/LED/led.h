#ifndef __LED_H
#define __LED_H	  
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define sebiaozuo     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//色标左-PE0
#define sebiaoyou     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//色标右-PE1
//#define bizhangzuo    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//避障左-PE2
#define bizhangyou    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//避障右-PE3
#define zhangai       GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//障碍  -PE4
#define zhongjianzuo  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//中间左-PE5
#define huiduzuo      GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)//灰度左-PE8
#define huiduyou      GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//灰度右-PE7
#define sebiaohou     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)//色标后-PE9

#define sebiaoqian    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//色标前-PB4
#define zhongjianyou  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//中间右-PC1
#define chukou  			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//中间右-PC1
#define rukou         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//迷宫  -PB6
#define bizhangzuo    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//避障左-PB7




#define dao1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)
#define dao2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)
#define dao3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
//#define moshi  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)

#define  LED1_ON	  	GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define	 LED1_OFF	  GPIO_ResetBits(GPIOC,GPIO_Pin_2)
#define  LED2_ON	  	GPIO_SetBits(GPIOC,GPIO_Pin_3)
#define	 LED2_OFF	  GPIO_ResetBits(GPIOC,GPIO_Pin_3)
//#define  LED3_ON	  	GPIO_SetBits(GPIOE,GPIO_Pin_9)
//#define	 LED3_OFF	  GPIO_ResetBits(GPIOE,GPIO_Pin_9)
#define  yuzhang    if(zhangai==1)

void LED_Init(void);//初始化

		 				    
#endif

