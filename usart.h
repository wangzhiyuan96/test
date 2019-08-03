#ifndef __USART_H
#define __USART_H


#include "stm32f10x.h"
#include "stdio.h"

extern u16 USART_STA;
extern u8 USART_BUF[200];


void usartInit(u32 baud);






#endif
