#ifndef __AT24C02_H
#define __AT24C02_H

#include "stm32f10x.h"
#include "i2c.h"
#include "delay.h"


void AT24C02_Write(u8 addr,u8 data);
u8 AT24C02_Read(u8 addr);



#endif

