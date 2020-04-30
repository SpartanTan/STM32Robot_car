
#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define zhijiaozuo  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define zhijiaoyou  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define zuoce  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define youce  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define qianbizhang  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define jidianqi  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define housebiao  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)
#define houbizhang  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)

void chuanganqi_Init(void);
#endif

