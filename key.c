#include "key.h"

void keyInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

u8 keyScan(u8 mode)
{
	static u8 key_set=1;
	if(mode)key_set=1;
	if(key_set&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);
		key_set=0;
		if(!KEY1) return KEY1_PRESS;
		else if (!KEY2)  return KEY2_PRESS;
		else if (!KEY3)  return KEY3_PRESS;
		else if (!KEY4)  return KEY4_PRESS;
	}
	else if (KEY1&&KEY2&&KEY3&&KEY4)key_set=1;
	
	return 0;
}