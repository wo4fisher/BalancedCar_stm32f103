#include "Timer.h"

u8 Time5msCnt=0;
u8 Time5msFlag=0;
u8 Time500msFlag=0;

void TIM1_Init(void)
{
	RCC->APB2ENR|=(1<<11);//��TIM1ʱ��
	TIM1->PSC=7200-1; //��72Mʱ�ӷ�Ƶ��ʹ�ü���Ƶ��Ϊ10k
	TIM1->ARR=50-1;//��ʱ5ms
	TIM1->CNT=0;//��ռ�����
	TIM1->CR1|=(1<<7);//�Զ���װ��Ԥװ��ʹ��
	TIM1->DIER|=(1<<0);//ʹ���ж�
	TIM1->DIER|=(1<<6);
	TIM1->CR1|=0X01;//��ʼ��ʱ
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
