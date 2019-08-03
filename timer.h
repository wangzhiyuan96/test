#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#include "usart.h"

void TIM3_Init(u16 Frq,u16 reload);
void TIM3_PWM_Init(u16 Frq,u16 reload);
void TIM1_Init(u16 Frq,u16 reload);
void TIM1_PWM_Init(u16 Frq,u16 reload);

#endif

