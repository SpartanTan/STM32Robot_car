#ifndef __LED_H
#define __LED_H	  
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define sebiaozuo     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//ɫ����-PE0
#define sebiaoyou     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//ɫ����-PE1
//#define bizhangzuo    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//������-PE2
#define bizhangyou    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//������-PE3
#define zhangai       GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//�ϰ�  -PE4
#define zhongjianzuo  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//�м���-PE5
#define huiduzuo      GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)//�Ҷ���-PE8
#define huiduyou      GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//�Ҷ���-PE7
#define sebiaohou     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)//ɫ���-PE9

#define sebiaoqian    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//ɫ��ǰ-PB4
#define zhongjianyou  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//�м���-PC1
#define chukou  			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//�м���-PC1
#define rukou         GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//�Թ�  -PB6
#define bizhangzuo    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//������-PB7




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

void LED_Init(void);//��ʼ��

		 				    
#endif

