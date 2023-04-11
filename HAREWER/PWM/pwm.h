#ifndef __PWM_H
#define	__PWM_H

#include "stm32f10x.h"

void	dj_int(u16 arr,u16 psc);
void	servo_int(u16 arr,u16 psc);
void timer_Init(int arr,int psc);


#endif

