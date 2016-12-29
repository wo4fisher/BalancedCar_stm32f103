#include "include.h"

u8 Time5msCnt=0;
u8 Time5msFlag=0;
u8 Time500msFlag=0;

void TIM3_Init(void)
{
	RCC->APB1ENR|=(1<<1);//��TIM7ʱ��
	TIM3->PSC=7200-1; //��72Mʱ�ӷ�Ƶ��ʹ�ü���Ƶ��Ϊ10k
	TIM3->ARR=50-1;//��ʱ5ms
	TIM3->CNT=0;//��ռ�����
	TIM3->CR1|=(1<<7);//�Զ���װ��Ԥװ��ʹ��
	TIM3->DIER|=(1<<0);//ʹ���ж�
	TIM3->DIER|=(1<<6);
	TIM3->CR1|=0X01;//��ʼ��ʱ
	MY_NVIC_Init(1,3,TIM3_IRQn,0);
}

void TIM3_IRQHandler(void)
{
	if(TIM3->SR)
	{
		TIM3->SR=0x0000;
		Time5msFlag=1;
		Time5msCnt++;
		if(Time5msCnt%100==0)
			Time500msFlag=1;
		if(Time5msCnt==200)
			Time5msCnt=0;
	}
}
