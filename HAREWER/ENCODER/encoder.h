#ifndef __ENCODER_H
#define __ENCODER_H
#include <stdio.h>
#include <stdint.h>
#define ENCODER_A   1 //TIM3  A6 A7
#define ENCODER_B   2 //TIM2  A0 A1

#define MAX_VALUE     65535


int Read_Encoder(uint8_t endcoder);
int Read_Position(uint8_t encoder);
void Encoder_A_init(void);
void Encoder_B_init(void);


#endif
