#ifndef __LED_H
#define __LED_H


#include "stm32f10x.h"

extern u16 led_status;


void ledInit(void);
void ledLock(u8 status);
void ledxSet(u16 ledx,u8 status);
void LED_Display();






#endif
