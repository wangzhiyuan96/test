#include "flash.h"

u16 Stm32_Flash_BUF[512];

void Stm32_Flash_WriteStr(u32 addr,u16 *pdata,u16 numtowrite)
{
	u32 Secpos;
	u32 off;
	u32 Secoff;
	u32 Secremain;
	u16 i;
	double temp;
	temp=addr;
	numtowrite=numtowrite/2;
	off=addr-FLASH_BASE;
	Secpos=off/1024;
	Secoff=(off%1024)/2;
	Secremain=512-Secoff;
	printf("第%d块-偏移%d-剩余%d\r\n",Secpos,Secoff,Secremain);
	FLASH_Unlock();
	for(i=0;i<512;i++) 
		Stm32_Flash_BUF[i]=Stm32_Flash_ReadHalfWord(Secpos*1024+FLASH_BASE+i*2);
	for(i=0;i<Secremain;i++)
	{
		if(0xFFFF!=Stm32_Flash_BUF[Secoff+i]) break;
			
	}
	if(i<Secremain)//擦除后再写入
	{
		printf("正在擦除第%d块...\r\n",Secpos);
		FLASH_ErasePage(Secpos*1024+FLASH_BASE);
		printf("正在写入...\r\n");
		for(i=0;i<numtowrite;i++)
			Stm32_Flash_BUF[Secoff+i]=pdata[i];
		for(i=0;i<512;i++)
			FLASH_ProgramHalfWord(Secpos*1024+FLASH_BASE+i*2,Stm32_Flash_BUF[i]);
		
	}else//直接写入
	{
		printf("正在写入...\r\n");
		if((temp/2-addr/2)>0.4)
		addr--;
		for(i=0;i<numtowrite;i++)
			FLASH_ProgramHalfWord(addr+i*2,pdata[i]);
	}
	FLASH_Lock();
	
	printf("写入完成！\r\n");
	
	
}
void Stm32_Flash_ReadStr(u32 addr,u16 *pdata,u16 numtoread)
{
	u16 i;
	double temp;
	temp=addr;
	if((temp/2-addr/2)>0.4)
	addr--;
	numtoread=numtoread/2;
	for(i=0;i<numtoread;i++)
		pdata[i]=Stm32_Flash_ReadHalfWord(addr+i*2);
	printf("读取完成！\r\n");
}

u16 Stm32_Flash_ReadHalfWord(u32 addr)
{
	return *(vu16*)addr;
}
