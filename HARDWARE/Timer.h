#ifndef TIMER_H
#define TIMER_H

#include "include.h"

extern u8 Time5msFlag;
extern u8 Time500msFlag;

extern void TIM3_Init(void);
void TIM3_IRQHandler(void);

#endif
