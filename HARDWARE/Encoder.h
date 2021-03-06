#ifndef ENCODER_H
#define ENCODER_H

#include "include.h"

#define EncoderLeftTim  4
#define EncoderRightTim 2
#define ENCODER_TIM_PERIOD (u16)(65535)   //不可大于65535 因为F103的定时器是16位的�

extern void Encoder_Init(void);
extern int Read_Encoder(u8 TIMX);
void TIM2_IRQHandler(void);

#endif
