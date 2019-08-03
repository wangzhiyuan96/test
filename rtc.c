#include "rtc.h"
calender_t calender;
void RTC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable the LSI OSC */
  RCC_LSICmd(ENABLE);
  /* Wait till LSI is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {}
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(40000);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* To output second signal on Tamper pin, the tamper functionality
       must be disabled (by default this functionality is disabled) */
  BKP_TamperPinCmd(DISABLE);

  /* Enable the RTC Second Output on Tamper Pin */
  BKP_RTCOutputConfig(BKP_RTCOutputSource_Second);
	
	  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}

void RTC_IRQHandler(void)
{
	u32 temp;
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
		temp=RTC_GetCounter();
		calender.Hour=temp/3600;
		calender.Min=(temp-calender.Hour*3600)/60;
		calender.Sec=temp%60;
		
		if(calender.Hour>=24) 
		{
			calender.Hour=0;
			RTC_SetCounter(1);
		}
		printf("%d-%d-%d\r\n",calender.Hour,calender.Min,calender.Sec);
    /* Clear Interrupt pending bit */
    RTC_ClearITPendingBit(RTC_FLAG_SEC);
  }
}

u32 RTC_Scan(void)
{
	u32 Hour,Min,Sec;
	printf("=============时间设置==============\r\n");
	printf("输入小时\r\n");
	USART_STA=0;
	while((USART_STA&0x8000)==0);
	USART_BUF[USART_STA&0x3FFF]='\0';
	Hour=atoi(USART_BUF);
	printf("输入了%s\r\n",USART_BUF);
	
	printf("输入分钟\r\n");
	USART_STA=0;
	while((USART_STA&0x8000)==0);
	USART_BUF[USART_STA&0x3FFF]='\0';
	Min=atoi(USART_BUF);
	printf("输入了%s\r\n",USART_BUF);
	
	printf("输入秒钟\r\n");
	USART_STA=0;
	while((USART_STA&0x8000)==0);
	USART_BUF[USART_STA&0x3FFF]='\0';
	Sec=atoi(USART_BUF);
	printf("输入了%s\r\n",USART_BUF);
	return (Hour*3600+Min*60+Sec);
	
}

void RTC_SetTime(u32 value)
{
	RTC_WaitForLastTask();
	RTC_SetCounter(value);
	RTC_WaitForLastTask();

}

