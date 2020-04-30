#ifndef _rgb3_H
#define _rgb3_H
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "sys.h"

extern u8 amount;
extern u8 Rgena,Ggena,Bgena;
extern double Ramount,Gamount,Bamount;
void whitebalance(void);
void duqui(void);
void yanse_init(void);
#endif

