#include "Coffee_bean.h"

void timer_handler(int signum)
{
	static int32 count = 0;
	printf("processing in timer handler %d times\n",++count);
	
}
