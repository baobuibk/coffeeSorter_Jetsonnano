#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "Coffee_bean.hpp"
#include <iostream>

const char *semName = "abc";
uint8 volatile 		cap_flag = 0;
external_devices 	de_cfbean;
uint16 			gpio = GPIO_RST_TIMER;		
//sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);


void timer_handler(int)
{
        static uint16   clk=0;
        clk++;
        //---------------------------
        //rst if get 50000 clk
        //---------------------------

        if (clk==50000)
        {
                clk = 0;
                de_cfbean.gpio_set_value(gpio,0);
        }
        else    de_cfbean.gpio_set_value(gpio,1);

        if ((clk%10000) == 0) // 0,05s->500 ,
        {
                cap_flag = 1;           //50ms
        }
}


//------------------------------------PARENT
void parent(void)
{
	struct sigaction sa;

	sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);
	
	if (sem_id == SEM_FAILED)
	{
		perror("Parent   : [sem_open] Failed\n"); 
		return;
	}
	printf("Parent Semaphore was opened\n");
	
	de_cfbean.gpio_export(gpio);                    //enable to export gpio
        de_cfbean.gpio_set_dir(gpio,DIR_OUT);           //set direction of gpio

        //--------------------------
        //config interupt
        //--------------------------
//      de_cfbean.config_interrupt(paddr_int);

        sigemptyset(&sa.sa_mask);
        sa.sa_flags     = 0;
        sa.sa_handler   = &timer_handler;                 // address of handler
        sigaction (SIGALRM, &sa, NULL);

        //--------------------------
        //config timer
        //--------------------------
        de_cfbean.config_timer_us(100);                 //100us
        de_cfbean.enable_timer();

	while(1)
	{
		if(cap_flag ==1)
		{
			cap_flag = 0;
			printf("Prepare to capture!\n");
			if (sem_post(sem_id) < 0)
                		printf("Parent   : [sem_post] Failed \n");
			//std::cout<<"Send semaphore ok!"<<std::endl;
		}
	}
	
	if (sem_close(sem_id) !=0)
	{
		perror("Child  : [sem_close] Failed\n"); 
		return;
	}
	
	if (sem_unlink(semName) < 0)
	{
		printf("Child  : [sem_unlink] Failed\n"); 
		return;
	}
}


//-------------------------------------CHILD
void child(void)
{
	int value;
	sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);
	if (sem_id == SEM_FAILED)
	{
		perror("Child   : [sem_open] Failed\n"); 
		return;
	}
	
	printf("Child Semaphore was opened ok!\n");

	while(1)
	{
		if (sem_getvalue(sem_id,&value) < 0)
		{
			printf("Error when get value\n");
			return;
		}
		std::cout<<"Current semaphore: "<<value<<std::endl;
 
		if (sem_wait(sem_id) < 0)
        		printf("Child   : [sem_wait] Failed \n");

		printf("Captured!\n");
		

	}
	
	
	
}

//---------------------------------------MAIN FUNCTION
int main()
{
	pid_t pid;

	pid = fork();

	if(pid == -1)
	{
		printf("Get error when creating a new process");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)	//child
	{
		child();		
	}

	else			//parent
	{
		int status;
		parent();
		wait(&status);		
	}
	return 0;

}
