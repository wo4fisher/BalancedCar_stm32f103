#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PWMLB   TIM1->CCR1  //PA8���
#define PWMLF   TIM1->CCR2
#define PWMRB   TIM1->CCR3
#define PWMRF   TIM1->CCR4  //PA11
#define motorEn PBin(3)
void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
#endif
