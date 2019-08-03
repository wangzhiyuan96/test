#include "at24c02.h"


void AT24C02_Write(u8 addr,u8 data)
{
	I2CStart();
	I2CSendByte(0xA0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	I2CSendByte(data);
	I2CWaitAck();
	I2CStop();
	
	delay_ms(10);
	
}


u8 AT24C02_Read(u8 addr)
{
	u8 data;
	
	I2CStart();
	I2CSendByte(0xA0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	
	I2CStart();
	I2CSendByte(0xA1);
	I2CWaitAck();
	data=I2CReceiveByte();
	I2CSendAck();
	I2CStop();
	
	return data;
}
