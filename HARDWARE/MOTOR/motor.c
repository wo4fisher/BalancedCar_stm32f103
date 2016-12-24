#include "motor.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
void MiniBalance_Motor_Init(void)
{
	RCC->APB2ENR|=1<<3;       //PORTB时钟使能   
	GPIOB->CRH&=0X0000FFFF;   //PORTB12 13 14 15推挽输出
	GPIOB->CRH|=0X22220000;   //PORTB12 13 14 15推挽输出
}
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		
	//RCC->APB2ENR|=1<<0;  //开启辅助时钟
	
	RCC->APB2ENR|=1<<2;
	//GPIOA->MODER |= 0X00AA0000;//pA8、9、10、11第二功能
	GPIOA->CRH&=0XFFFF0000;//PA8、9、10、11输出 
	GPIOA->CRH|=0X0000BBBB;//复用功能输出 
	GPIOA->ODR|=1<<8;//PA8 上拉
	GPIOA->ODR|=1<<9;
	GPIOA->ODR|=1<<10;
	GPIOA->ODR|=1<<11;

	RCC->APB2ENR|=1<<11; //TIM1时钟使能
	TIM1->ARR=arr;//计数器自动重装值 
	TIM1->PSC=psc;//179 分频
	
	TIM1->EGR |= 1<<0; // 初始化所有寄存器

	TIM1->CCMR1|=6<<4; //CH1 PWM1模式 
	TIM1->CCMR1|=1<<3; //CH1预装载使能
	TIM1->CCMR1|=6<<12; //CH2 PWM1 模式
	TIM1->CCMR1|=1<<11; //CH2预装载使能
	TIM1->CCMR2|=6<<4; //CH3 PWM1模式 
	TIM1->CCMR2|=1<<3; //CH3预装载使能
	TIM1->CCMR2|=6<<12; //CH4 PWM1 模式 
	TIM1->CCMR2|=1<<11; //CH4预装载使能

	//TIM1->CR1|=1<<4; // 向下计数模式

	TIM1->CCER|=1<<0; //OC1 输出使能 
	TIM1->CCER|=1<<4; //OC2 输出使能
	TIM1->CCER|=1<<8; //OC3 输出使能 
	TIM1->CCER|=1<<12; //OC4 输出使能

	TIM1->BDTR |=1<<15; // 开启 OC和 OCN输出

    //
	TIM1->CCR1 = 0; //设置占空比 0~100% 
	TIM1->CCR2 = 1100; //左轮 1100为电机死区
	TIM1->CCR3 = 0; 
	TIM1->CCR4 = 1100; 

    TIM1->CR1|=1<<7; //ARPE使能自动重装预装载允许位
	TIM1->CR1|=1<<0; //使能定时器
} 

