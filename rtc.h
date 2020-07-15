#ifndef __RTC_H
#define __RTC_H

#include "stm32f10x.h"
#include "usart.h"
#include "stdlib.h"
#include "stdio.h"
typedef struct 
{
	u8 Hour;
	u8 Min;
	u8 Sec;

}calender_t;

extern calender_t calender;

void RTC_Configuration(void);
u32 RTC_Scan(void);
void RTC_SetTime(u32 value);

#endif