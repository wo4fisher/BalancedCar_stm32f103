#include "include.h"

  /**************************************************************************
平衡车
**************************************************************************/

int main(void)
{ 
	Stm32_Clock_Init(9);            //=====系统时钟设置
	delay_init(72);                 //=====延时初始化
	delay_ms(1000);
	LED_Init();                     //=====初始化与 LED 连接的硬件接口
	uart_init(72,115200);           //=====初始化串口1
	LCD5110_init();
	IIC_Init();
	delay_ms(100);
	MPU_Init();
	delay_ms(500);
	Motor_PWM_Init(7200-1,0);
	TIM1_Init();
	LCD5110_clear();
	main_window_proc();
	//Get_Angle_Init();
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
		//display_proc();
	} 
}
