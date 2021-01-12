#include "uart.h"


int main()
{
	Uart test;
	uint8 i;
	uint8 a[10];
	for (i=0;i<10;i++) a[i] =i+48;
	test.sendUart(a);
	test.closeUart();
	return 0;



}
