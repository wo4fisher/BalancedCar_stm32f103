#include "motor.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
void MiniBalance_Motor_Init(void)
{
	RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ��   
	GPIOB->CRH&=0X0000FFFF;   //PORTB12 13 14 15�������
	GPIOB->CRH|=0X22220000;   //PORTB12 13 14 15�������
}
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		
	//RCC->APB2ENR|=1<<0;  //��������ʱ��
	
	RCC->APB2ENR|=1<<2;
	//GPIOA->MODER |= 0X00AA0000;//pA8��9��10��11�ڶ�����
	GPIOA->CRH&=0XFFFF0000;//PA8��9��10��11��� 
	GPIOA->CRH|=0X0000BBBB;//���ù������ 
	GPIOA->ODR|=1<<8;//PA8 ����
	GPIOA->ODR|=1<<9;
	GPIOA->ODR|=1<<10;
	GPIOA->ODR|=1<<11;

	RCC->APB2ENR|=1<<11; //TIM1ʱ��ʹ��
	TIM1->ARR=arr;//�������Զ���װֵ 
	TIM1->PSC=psc;//179 ��Ƶ
	
	TIM1->EGR |= 1<<0; // ��ʼ�����мĴ���

	TIM1->CCMR1|=6<<4; //CH1 PWM1ģʽ 
	TIM1->CCMR1|=1<<3; //CH1Ԥװ��ʹ��
	TIM1->CCMR1|=6<<12; //CH2 PWM1 ģʽ
	TIM1->CCMR1|=1<<11; //CH2Ԥװ��ʹ��
	TIM1->CCMR2|=6<<4; //CH3 PWM1ģʽ 
	TIM1->CCMR2|=1<<3; //CH3Ԥװ��ʹ��
	TIM1->CCMR2|=6<<12; //CH4 PWM1 ģʽ 
	TIM1->CCMR2|=1<<11; //CH4Ԥװ��ʹ��

	//TIM1->CR1|=1<<4; // ���¼���ģʽ

	TIM1->CCER|=1<<0; //OC1 ���ʹ�� 
	TIM1->CCER|=1<<4; //OC2 ���ʹ��
	TIM1->CCER|=1<<8; //OC3 ���ʹ�� 
	TIM1->CCER|=1<<12; //OC4 ���ʹ��

	TIM1->BDTR |=1<<15; // ���� OC�� OCN���

    //
	TIM1->CCR1 = 0; //����ռ�ձ� 0~100% 
	TIM1->CCR2 = 1100; //���� 1100Ϊ�������
	TIM1->CCR3 = 0; 
	TIM1->CCR4 = 1100; 

    TIM1->CR1|=1<<7; //ARPEʹ���Զ���װԤװ������λ
	TIM1->CR1|=1<<0; //ʹ�ܶ�ʱ��
} 

