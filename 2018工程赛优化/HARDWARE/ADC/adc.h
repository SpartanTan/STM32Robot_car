#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
////////////////////////////////////////////////////////////////////////////////// 
extern u16 Exposure_tim;
extern u8 ao_d[128];

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times);
void SI(int a);
void CLK(int a);
u16 CCD_Find(void);
void GPIO_Config(void);
#endif 
