#include "Coffee_bean.h"
#include <stdio.h>



void timer_handler(int sig)
{
	static uint8 count_in=0;
	flag_timer = ENABLE;
	printf("processing in timer handler %d\n",++count_in);
	
}
