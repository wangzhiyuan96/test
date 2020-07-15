#ifndef __KEY_H
#define __KEY_H


#include "stm32f10x.h"
#include "delay.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define KEY4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)


#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4

void keyInit();
u8 keyScan(u8 mode);





#endif
