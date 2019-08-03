#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f10x.h"
#include "usart.h"
void Stm32_Flash_WriteStr(u32 addr,u16 *pdata,u16 numtowrite);
void Stm32_Flash_ReadStr(u32 addr,u16 *pdata,u16 numtoread);
u16 Stm32_Flash_ReadHalfWord(u32 addr);

#endif