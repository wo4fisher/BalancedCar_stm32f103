#ifndef TIMER_H
#define TIMER_H

#include "include.h"

extern u8 Time5msFlag;
extern u8 Time500msFlag;

extern void TIM1_Init(void);
void TIM1_UP_IRQHandler(void);

#endif
