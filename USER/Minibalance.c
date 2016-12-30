#include "include.h"

  /**************************************************************************
平衡车
**************************************************************************/

int main(void)
{ 
	int16_t i;
	Stm32_Clock_Init(9);            //=====系统时钟设置
	delay_init(72);                 //=====延时初始化
	delay_ms(500);
	LED_Init();                     //=====初始化与 LED 连接的硬件接口
	uart_init(72,115200);           //=====初始化串口1
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
