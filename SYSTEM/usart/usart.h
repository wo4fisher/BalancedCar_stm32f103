#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 
void usart1_send(u8 data);
void usart1_sendbuff(u8 *buff,u8 len);
void uart_init(u32 pclk2,u32 bound);
#endif	   
















