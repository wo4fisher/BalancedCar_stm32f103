#include "Encoder.h"

void Encoder_Left_Init(void)
{
	RCC->APB1ENR|=1<<2;     //TIM4Ê±ÖÓÊ¹ÄÜ
	RCC->APB2ENR|=1<<3;     //Ê¹ÄÜPORTBÊ±ÖÓ
	GPIOB->CRL&=0X00FFFFFF; //PB6 PB7
	GPIOB->CRL|=0X44000000; //¸¡¿ÕÊäÈë
	TIM4->DIER|=1<<0;   //ÔÊÐí¸üÐÂÖÐ¶Ï				
	TIM4->DIER|=1<<6;   //ÔÊÐí´¥·¢ÖÐ¶Ï
	MY_NVIC_Init(1,3,TIM4_IRQn,1);
	TIM4->PSC = 0x0;//Ô¤·ÖÆµÆ÷
	TIM4->ARR = ENCODER_TIM_PERIOD;//Éè¶¨¼ÆÊýÆ÷×Ô¶¯ÖØ×°Öµ 
	TIM4->CR1 &=~(3<<8);// Ñ¡ÔñÊ±ÖÓ·ÖÆµ£º²»·ÖÆµ
	TIM4->CR1 &=~(3<<5);// Ñ¡Ôñ¼ÆÊýÄ£Ê½:±ßÑØ¶ÔÆëÄ£Ê½
		
	TIM4->CCMR1 |= 1<<0; //CC1S='01' IC1FP1Ó³Éäµ½TI1
	TIM4->CCMR1 |= 1<<8; //CC2S='01' IC2FP2Ó³Éäµ½TI2
	TIM4->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1²»·´Ïà£¬IC1FP1=TI1
	TIM4->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2²»·´Ïà£¬IC2FP2=TI2
	TIM4->CCMR1 |= 3<<4; //	IC1F='1000' ÊäÈë²¶»ñ1ÂË²¨Æ÷
	TIM4->SMCR |= 3<<0;	 //SMS='011' ËùÓÐµÄÊäÈë¾ùÔÚÉÏÉýÑØºÍÏÂ½µÑØÓÐÐ§
	TIM4->CR1 |= 0x01;    //CEN=1£¬Ê¹ÄÜ¶¨Ê±Æ
}
	
void Encoder_Right_Init(void)
{
	RCC->APB1ENR|=1<<0;     //TIM2Ê±ÖÓÊ¹ÄÜ
	RCC->APB2ENR|=1<<2;    //Ê¹ÄÜPORTAÊ±ÖÓ
	GPIOA->CRL&=0XFFFFFF00;//PA0 PA1
	GPIOA->CRL|=0X00000044;//¸¡¿ÕÊäÈë
	TIM2->DIER|=1<<0;   //ÔÊÐí¸üÐÂÖÐ¶Ï				
	TIM2->DIER|=1<<6;   //ÔÊÐí´¥·¢ÖÐ¶Ï
	MY_NVIC_Init(1,3,TIM2_IRQn,1);
	TIM2->PSC = 0x0;//Ô¤·ÖÆµÆ÷
	TIM2->ARR = ENCODER_TIM_PERIOD;//Éè¶¨¼ÆÊýÆ÷×Ô¶¯ÖØ×°Öµ 
	TIM2->CR1 &=~(3<<8);// Ñ¡ÔñÊ±ÖÓ·ÖÆµ£º²»·ÖÆµ
	TIM2->CR1 &=~(3<<5);// Ñ¡Ôñ¼ÆÊýÄ£Ê½:±ßÑØ¶ÔÆëÄ£Ê½
		
	TIM2->CCMR1 |= 1<<0; //CC1S='01' IC1FP1Ó³Éäµ½TI1
	TIM2->CCMR1 |= 1<<8; //CC2S='01' IC2FP2Ó³Éäµ½TI2
	TIM2->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1²»·´Ïà£¬IC1FP1=TI1
	TIM2->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2²»·´Ïà£¬IC2FP2=TI2
	TIM2->CCMR1 |= 3<<4; //	IC1F='1000' ÊäÈë²¶»ñ1ÂË²¨Æ÷
	TIM2->SMCR |= 3<<0;	 //SMS='011' ËùÓÐµÄÊäÈë¾ùÔÚÉÏÉýÑØºÍÏÂ½µÑØÓÐÐ§
	TIM2->CR1 |= 0x01;    //CEN=1£¬Ê¹ÄÜ¶¨Ê±Æ÷
}

int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
    switch(TIMX)
	{
		case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		default:  Encoder_TIM=0;break;
	}
	return Encoder_TIM;
}

void Encoder_Init(void)
{
	Encoder_Left_Init();
	Encoder_Right_Init();
}

void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//Òç³öÖÐ¶Ï
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î» 	    
}

void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//Òç³öÖÐ¶Ï
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//Çå³ýÖÐ¶Ï±êÖ¾Î» 	    
}