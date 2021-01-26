#include "uart.h"
#include "crc16.h"
#include "afproto.h"
#include "stdio.h"



#define START_BIT 	0x12
#define STOP_BIT 	0x13
#define ESC 		0x7D
#define OR_FLAG		0x20

//uint8 encoding_data(uint8 *p_send_buff,uint8 channel,uint16 shooting_time);

int main()
{
	uint16 shooting_time = 0x1309;
	uint8  channel = 0x11;
	uint16  lenbuff =3;
	Uart test;

	uint8 msb_shooting_time = (shooting_time >> 8) & 0xFF;
	uint8 lsb_shooting_time = (shooting_time >> 0) & 0xFF;

	const char buff[3] = {channel, msb_shooting_time,lsb_shooting_time};
	char encode_buff[20];
	uint8 encode_buff_Uart[20];
	//	uint8 dest_len;
	uint16 p_endcode_len;
	//int   a;

	//	uint8 i=0;
//	for (i=0; i<10;i++) send_buff[i] = 0;


	afproto_frame_data(buff, lenbuff ,encode_buff, &p_endcode_len); 

	
	for (uint8 i=0; i<20;i++) 
	{
		encode_buff_Uart[i] = (uint8)encode_buff[i];
		printf("%x \n", encode_buff_Uart[i]);
	}
	
//	uint8 a[10];
//	for (i=0;i<10;i++) a[i] =i+48;

//	encoding_data(send_buff,channel,shooting_time);
	
	test.sendUart(encode_buff_Uart);
	test.closeUart();
	return 0;

}
/*
uint8 encoding_data(uint8 *p_send_buff, uint8 channel, uint16 shooting_time)
{
	uint8 msb_shooting_time = 0;
	uint8 lsb_shooting_time = 0;

	*p_send_buff++ = 0x12;
	//===================================Channel
	if ((channel == START_BIT) | (channel == STOP_BIT) | (channel == ESC))
	{
		*p_send_buff++ = 0x7D;
		*p_send_buff++ = channel ^ OR_FLAG;
	}
	else *p_send_buff++ = channel;
	
	//=================================== Shooting time
	
	msb_shooting_time = (shooting_time >> 8) & 0xFF;
	lsb_shooting_time = (shooting_time >> 0) & 0xFF;
	
	if ((msb_shooting_time == START_BIT) | (msb_shooting_time == STOP_BIT) | (msb_shooting_time == ESC))
	{
		*p_send_buff++ = 0x7D;
		*p_send_buff++ = msb_shooting_time ^ OR_FLAG;
	}
	else 	*p_send_buff++ = msb_shooting_time;
	//-----------------------------------
	if ((lsb_shooting_time == START_BIT) | (lsb_shooting_time == STOP_BIT) | (lsb_shooting_time == ESC))
	{
		*p_send_buff++ = 0x7D;
		*p_send_buff++ = lsb_shooting_time ^ OR_FLAG;
	}
	else 	*p_send_buff++ = lsb_shooting_time;
 
	//=================================== CRC
	
	return 0;
}
*/


