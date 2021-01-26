#include "GPIOnew.h"
#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
//#include "uart.h"

typedef unsigned int uint16;
typedef unsigned char uint8; 

#define MAX_RST 50
uint8 Trigger = 0;
//uint8	count = 0;

uint16	gpio = GPIO_RST_TIMER;


void disable_timer(struct itimerval timer1);


void timer_handler(int)
{
	static uint8 count=0;
	count++;
//	printf("%d \n",count);
		
	if (count%2 == 1) gpio_set_value(gpio,1);
	else		  gpio_set_value(gpio,0);
	
//	if (count == MAX_RST) Trigger = 1;
}	


int main()
{
	struct itimerval timer1;
	struct sigaction sa;

	//======================= setting GPIO
	gpio_export(gpio);
	gpio_set_dir(gpio,DIR_OUT);


	//======================= setting interrupt
 	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &timer_handler;			// address of handler	
 	sigaction (SIGALRM, &sa, NULL);		
	//======================= config timer
	timer1.it_value.tv_sec 		= 0;
	timer1.it_value.tv_usec 	= 100;

	timer1.it_interval.tv_sec 	= 0;
	timer1.it_interval.tv_usec 	= 100;
	
	//======================= enable timer
	setitimer(ITIMER_REAL,&timer1, NULL);
	
	while(1);
	
	disable_timer(timer1);
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


