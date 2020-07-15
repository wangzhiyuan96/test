#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void delay_init(void);
void delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);


#endif

