#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 								  
//********************************************************************************
//void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void tingzhi(void);
void pwm_Init(void);
void speed1(u16 zuo,u16 you);
void zhuanwan(u16 zuo,u16 you);
void daoche(u16 zuo,u16 you);
void yuandiyouzhuan(u16 zuo,u16 you);
void yuandizuozhuan(u16 zuo,u16 you);
#endif
