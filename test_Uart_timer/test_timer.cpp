#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
#include "uart.h"
typedef unsigned int uint16;
typedef unsigned char uint8; 

#define MAX_RST 50
uint8 Trigger = 0;

void disable_timer(struct itimerval timer1);


void timer_handler(int)
{
	static uint16 count=0;
	count++;
	printf("%d \n",count);
	if (count == MAX_RST) Trigger = 1;
}	


int main()
{
	struct itimerval timer1;
	struct sigaction sa;


	//======================= setting interrupt
 	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &timer_handler;			// address of handler	
 	sigaction (SIGVTALRM, &sa, NULL);		
	//======================= config timer
	timer1.it_value.tv_sec 		= 1;
	timer1.it_value.tv_usec 	= 0;

	timer1.it_interval.tv_sec 	= 1;
	timer1.it_interval.tv_usec 	= 0;
	
	//======================= enable timer
	setitimer(ITIMER_VIRTUAL,&timer1, NULL);

	while(1)
	{
		if (Trigger == 1)
		{
			Trigger = 0;
			disable_timer(timer1);
			break;
		}
	}
	return 0;
}

void disable_timer(struct itimerval timer1)
{
	timer1.it_value.tv_sec 		= 0;	// set 0 to disable timer
	timer1.it_value.tv_usec 	= 0;	// set 0 to disable timer

	timer1.it_interval.tv_sec 	= 0;	// set 0 to use timer only once
	timer1.it_interval.tv_usec 	= 0;	// set 0 to use timer only once
	setitimer(ITIMER_VIRTUAL,&timer1, NULL);
}


