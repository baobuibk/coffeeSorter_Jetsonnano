#include "uart.h"

#define START_BIT 	0x12
#define STOP_BIT 	0x13
#define ESC 		0x7D
#define OR_FLAG		0x20

uint8 encoding_data(uint8 *p_send_buff,uint8 channel,uint16 shooting_time);

int main()
{
	Uart test;
	uint8 send_buff[10]
	uint8 i;
	for (uint8 i=0; i<10;i++) send_buff[i] = 0;
//	uint8 a[10];
//	for (i=0;i<10;i++) a[i] =i+48;

	encoding_data(send_buff,channel,shooting_time);
	test.sendUart(send_buff);
	test.closeUart();
	return 0;



}

uint8 encoding_data(uint8 *p_send_buff, uint8 channel, uint16 shooting_time)
{
	uint8 msb_shooting_time = 0;
	uint8 lsb_shooting_time = 0;

	*p_send_buff++ = 0x12;
	//===================================Channel
	if ((channel == START_BIT) | channel == STOP_BIT | channel == ESC)
	{
		*p_send_buff++ = 0x7D;
		*p_send_buff++ = channel | OR_FLAG;
	}
	else *p_send_buff++ = channel;
	
	//=================================== Shooting time
	
	msb_shooting_time = (shooting_time >> 8) & 0xFF;
	lsb_shooting_time = (shooting_time >> 0) & 0xFF;
	
	if (msb_shooting_time == START_BIT | msb_shooting_time == STOP_BIT | msb_shooting_time == ESC)
	{
		*p_send_buff++ = 0x7D;
		*p_send_buff++ = msb_shooting_time | OR_FLAG;
	}
	else 	*p_send_buff++ = msb_shooting_time;
	//-----------------------------------
	if (lsb_shooting_time == START_BIT | lsb_shooting_time == STOP_BIT | lsb_shooting_time == ESC)
	{
		*p_send_buff++ = 0x7D;
		*p_send_buff++ = lsb_shooting_time | OR_FLAG;
	}
	else 	*p_send_buff++ = lsb_shooting_time;
 
	//=================================== CRC
	
}

