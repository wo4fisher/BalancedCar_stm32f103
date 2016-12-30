#include "Timer.h"

u8 Time5msCnt=0;
u8 Time5msFlag=0;
u8 Time500msFlag=0;

void TIM1_Init(void)
{
	RCC->APB2ENR|=(1<<11);//打开TIM1时钟
	TIM1->PSC=7200-1; //对72M时钟分频，使得计数频率为10k
	TIM1->ARR=50-1;//定时5ms
	TIM1->CNT=0;//清空计数器
	TIM1->CR1|=(1<<7);//自动重装载预装载使能
	TIM1->DIER|=(1<<0);//使能中断
	TIM1->DIER|=(1<<6);
	TIM1->CR1|=0X01;//开始计时
	MY_NVIC_Init(1,3,TIM1_UP_IRQn,0);
}

void TIM1_UP_IRQHandler(void)
{
	if(TIM1->SR)
	{
		TIM1->SR=0x0000;
		Time5msFlag=1;
		Time5msCnt++;
		if(Time5msCnt%100==0)
			Time500msFlag=1;
		if(Time5msCnt==200)
			Time5msCnt=0;
	}
}
