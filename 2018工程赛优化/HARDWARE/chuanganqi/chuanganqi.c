#include "chuanganqi.h"

void chuanganqi_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
}


