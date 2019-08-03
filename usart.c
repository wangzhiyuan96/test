#include "usart.h"

u16 USART_STA=0;
u8 USART_BUF[200];


struct __FILE
{
	int handle;
};

FILE __stdout;

int fputc(int ch, FILE *f)
{ 
	/* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}
	/* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (uint8_t) ch);

  return ch;
}

void usartInit(u32 baud)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	/* Configure USARTy Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
  USART_InitStructure.USART_BaudRate = baud;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  USART_Init(USART2, &USART_InitStructure);

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  USART_Cmd(USART2, ENABLE);
	

	
}

void USART2_IRQHandler(void)
{
	u8 res;
	
	res = USART_ReceiveData(USART2);
	
		if((USART_STA&0x8000)==0)
		{
			if(USART_STA&0x4000)
			{
				if(res==0x0A)USART_STA|=0x8000;
				else USART_STA=0;				
			}else
			{
				if(res==0x0D)USART_STA|=0x4000;
				else 
				{
					USART_BUF[USART_STA&0X3FFF]=res;
					USART_STA++;
				}
			}
		}
   
}

/*		main()...
		if(USART_STA&0x8000)
		{
			USART_BUF[USART_STA&0x3fff]='\0';
			printf("ƒ„ ‰»Îµƒ «£∫%s\r\n",USART_BUF);
			USART_STA=0;
		}
*/
