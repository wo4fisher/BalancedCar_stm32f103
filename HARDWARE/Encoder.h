#ifndef ENCODER_H
#define ENCODER_H

#include "include.h"

#define EncoderLeftTim  4
#define EncoderRightTim 2
#define ENCODER_TIM_PERIOD (u16)(65535)   //²»¿É´óÓÚ65535 ÒòÎªF103µÄ¶¨Ê±Æ÷ÊÇ16Î»µÄ¡

extern void Encoder_Init(void);
extern int Read_Encoder(u8 TIMX);
void TIM2_IRQHandler(void);

#endif
