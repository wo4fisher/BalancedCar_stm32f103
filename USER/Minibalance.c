#include "include.h"

  /**************************************************************************
ƽ�⳵
**************************************************************************/

int main(void)
{ 
	int16_t i;
	Stm32_Clock_Init(9);            //=====ϵͳʱ������
	delay_init(72);                 //=====��ʱ��ʼ��
	delay_ms(500);
	LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	uart_init(72,115200);           //=====��ʼ������1
	LCD5110_init();
	LCD5110_clear();
	IIC_Init();
	delay_ms(100);
	MPU_Init();
	Motor_PWM_Init(7200-1,0);
	TIM1_Init();
	i=400;
	while(i)
	{
		if(Time500msFlag)
		{
			Time500msFlag=0;
			LED=!LED;
			//printf("Running\n");
		}	
		if(Time5msFlag)
		{
			Time5msFlag=0;
			Get_RT_Att();
			i--;
		}
		display_proc();
	}
	while(1)
	{
		if(Time500msFlag)
		{
			Time500msFlag=0;
			LED=!LED;
			//printf("Running\n");
		}	
		if(Time5msFlag)
		{
			Time5msFlag=0;
			Get_RT_Att();
			Car_Control();
		}
		display_proc();
	} 
}
