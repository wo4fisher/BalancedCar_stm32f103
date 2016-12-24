#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define PWMLB   TIM1->CCR1  //PA8左后
#define PWMLF   TIM1->CCR2
#define PWMRB   TIM1->CCR3
#define PWMRF   TIM1->CCR4  //PA11
#define motorEn PBin(3)
void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
#endif
