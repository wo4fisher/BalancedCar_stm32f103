#ifndef MOTOR_H
#define MOTOR_H

#include "include.h"

#define PWMRB   TIM3->CCR1  //ср╨С
#define PWMRF   TIM3->CCR2
#define PWMLB   TIM3->CCR3
#define PWMLF   TIM3->CCR4  //

extern void Motor_PWM_Init(u16 arr,u16 psc);
#endif
