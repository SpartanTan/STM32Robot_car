#ifndef __duoj_H
#define __duoj_H	
#include "sys.h"

/******¶æ»ú******
	 		PC6->#1
			PC7->#2	
			PC8->#3
			PC9->#4
*******************/

void TIM3_PWM_Init(u16 arr,u16 psc);
void duoji(void);
void duoji1324(u16 one,u16 two,u16 three,u16 four);
void duoji1234kuai(u16 one,u16 two,u16 three,u16 four);
void duoji1234(u16 one,u16 two,u16 three,u16 four);
void duoji1243(u16 one,u16 two,u16 three,u16 four);
void duoji1342(u16 one,u16 two,u16 three,u16 four);
void duoji2341(u16 one,u16 two,u16 three,u16 four);
void duoji3412(u16 one,u16 two,u16 three,u16 four);
void duoji3412kuai(u16 one,u16 two,u16 three,u16 four);

void xiaoduoji(int mod);
void GPIOD_Init(void);
void mantiao(u16 duo2_set,u16 duo3_set,u16 duo4_set);
void mantiao1(u16 duo2_set,u16 duo3_set,u16 duo4_set);
#endif


