#include "Motor.h"

void Motor_PWM_Init(u16 arr,u16 psc)
{	
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<3;  //开启gpio时钟
	
	GPIOA->CRL&=0X00FFFFFF;//PA6、7输出 
	GPIOA->CRL|=0XBB000000;//复用功能输出 
	GPIOA->ODR|=1<<6;//PA8 上拉
	GPIOA->ODR|=1<<7;	
	GPIOB->CRL&=0XFFFFFF00;//PB0、1输出 
	GPIOB->CRL|=0X000000BB;//复用功能输出 
	GPIOB->ODR|=1<<0;//PA8 上拉
	GPIOB->ODR|=1<<1;

	RCC->APB1ENR|=1<<1; //TIM3时钟使能
	TIM3->ARR=arr;//计数器自动重装值 
	TIM3->PSC=psc;//179 分频
	
	TIM3->EGR |= 1<<0; // 初始化所有寄存器

	TIM3->CCMR1|=6<<4; //CH1 PWM1模式 
	TIM3->CCMR1|=1<<3; //CH1预装载使能
	TIM3->CCMR1|=6<<12; //CH2 PWM1 模式
	TIM3->CCMR1|=1<<11; //CH2预装载使能
	TIM3->CCMR2|=6<<4; //CH3 PWM1模式 
	TIM3->CCMR2|=1<<3; //CH3预装载使能
	TIM3->CCMR2|=6<<12; //CH4 PWM1 模式 
	TIM3->CCMR2|=1<<11; //CH4预装载使能

	//TIM1->CR1|=1<<4; // 向下计数模式

	TIM3->CCER|=1<<0; //OC1 输出使能 
	TIM3->CCER|=1<<4; //OC2 输出使能
	TIM3->CCER|=1<<8; //OC3 输出使能 
	TIM3->CCER|=1<<12; //OC4 输出使能

	TIM3->BDTR |=1<<15; // 开启 OC和 OCN输出

    //
	TIM3->CCR1 = 1100; //设置占空比 0~100% 
	TIM3->CCR2 = 1100; //左轮 1100为电机死区
	TIM3->CCR3 = 1100; 
	TIM3->CCR4 = 1100; 

    TIM3->CR1|=1<<7; //ARPE使能自动重装预装载允许位
	TIM3->CR1|=1<<0; //使能定时器
} 
