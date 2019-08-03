#include "led.h"

u16 led_status=0xFEFF;

void ledInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);


	GPIO_InitStructure.GPIO_Pin = 
	GPIO_Pin_8|GPIO_Pin_9|
	GPIO_Pin_10|GPIO_Pin_11|
	GPIO_Pin_12|GPIO_Pin_13|
	GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC,GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOD,GPIO_InitStructure.GPIO_Pin);
	
}

void ledLock(u8 status)
{
	if (status)
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
	else 
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
}

void ledxSet(u16 ledx,u8 status)
{
	if (status)
		GPIOC->ODR&=(0xFEFF<<ledx);
	else 
		GPIOC->ODR|=(0x0100<<ledx);

}

void LED_Display()
{
	ledLock(0);
	GPIO_Write(GPIOC,led_status);
	ledLock(1);
}


/*		Á÷Ë®µÆ
		for(i=0;i<8;i++)
		{
			LED_Display();
			delay_ms(100);
			led_status=led_status<<1;
		}led_status=0xFEFF;
*/
