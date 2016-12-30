#include "Motor.h"

void Motor_PWM_Init(u16 arr,u16 psc)
{	
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<3;  //����gpioʱ��
	
	GPIOA->CRL&=0X00FFFFFF;//PA6��7��� 
	GPIOA->CRL|=0XBB000000;//���ù������ 
	GPIOA->ODR|=1<<6;//PA8 ����
	GPIOA->ODR|=1<<7;	
	GPIOB->CRL&=0XFFFFFF00;//PB0��1��� 
	GPIOB->CRL|=0X000000BB;//���ù������ 
	GPIOB->ODR|=1<<0;//PA8 ����
	GPIOB->ODR|=1<<1;

	RCC->APB1ENR|=1<<1; //TIM3ʱ��ʹ��
	TIM3->ARR=arr;//�������Զ���װֵ 
	TIM3->PSC=psc;//179 ��Ƶ
	
	TIM3->EGR |= 1<<0; // ��ʼ�����мĴ���

	TIM3->CCMR1|=6<<4; //CH1 PWM1ģʽ 
	TIM3->CCMR1|=1<<3; //CH1Ԥװ��ʹ��
	TIM3->CCMR1|=6<<12; //CH2 PWM1 ģʽ
	TIM3->CCMR1|=1<<11; //CH2Ԥװ��ʹ��
	TIM3->CCMR2|=6<<4; //CH3 PWM1ģʽ 
	TIM3->CCMR2|=1<<3; //CH3Ԥװ��ʹ��
	TIM3->CCMR2|=6<<12; //CH4 PWM1 ģʽ 
	TIM3->CCMR2|=1<<11; //CH4Ԥװ��ʹ��

	//TIM1->CR1|=1<<4; // ���¼���ģʽ

	TIM3->CCER|=1<<0; //OC1 ���ʹ�� 
	TIM3->CCER|=1<<4; //OC2 ���ʹ��
	TIM3->CCER|=1<<8; //OC3 ���ʹ�� 
	TIM3->CCER|=1<<12; //OC4 ���ʹ��

	TIM3->BDTR |=1<<15; // ���� OC�� OCN���

    //
	TIM3->CCR1 = 1100; //����ռ�ձ� 0~100% 
	TIM3->CCR2 = 1100; //���� 1100Ϊ�������
	TIM3->CCR3 = 1100; 
	TIM3->CCR4 = 1100; 

    TIM3->CR1|=1<<7; //ARPEʹ���Զ���װԤװ������λ
	TIM3->CR1|=1<<0; //ʹ�ܶ�ʱ��
} 
