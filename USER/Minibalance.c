#include "include.h"

  /**************************************************************************
ƽ�⳵
**************************************************************************/

int main(void)
{ 
	Stm32_Clock_Init(9);            //=====ϵͳʱ������
	delay_init(72);                 //=====��ʱ��ʼ��
	delay_ms(2000);
	TIM1_Init();
	LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	uart_init(72,115200);           //=====��ʼ������1
	IIC_Init();
	delay_ms(100);
	MPU_Init();
	while(1)
	{
		if(Time500msFlag)
		{
			Time500msFlag=0;
			LED=!LED;
			Get_MPUdata();
			printf("Running\n");

		}	
	} 
}
