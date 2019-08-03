#include "delay.h"

static __IO uint32_t TimingDelay;

void delay_init(void)
{
	SysTick_Config(SystemCoreClock/1000);
}

void delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}
