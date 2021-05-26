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

#define SIZE 10				// size of the test matrix


//-------------- Variable for process
const char *semName = "abc";            // Semaphore name used for synchronizing
//sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);




//-------------- Variable for thread
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;	//Initialize the value for mutex


//-------------- Other
uint8 volatile 		cap_flag = 0;			// Capture flag, be used to check the status of capture
external_devices 	de_cfbean;
uint16 			gpio = GPIO_RST_TIMER;		// reset pin	

int 			matrix1[SIZE][SIZE];		// Using to test

//===================================
//     	TIMER HANDLER
//
//===================================
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

        if ((clk%500) == 0) // 0,05s->500 ,
        {
                cap_flag = 1;           //50ms
        }
}


//===================================
//		PARENT
//	USING TO CONTROL TIMER
//
//===================================

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
	//		printf("Prepare to capture!\n");
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




//===================================
//		THREAD 1
//	USING TO WRITE VALUE INTO ARRAY
//
//===================================

void *write_arr(void* arg)
{
        static int status = 0;
	static uint8 count = 0;

	//-------------------------- Open semaphore
	// SEMAPHORE
	//---------------
	sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);
	
	if (sem_id == SEM_FAILED)
	{
		perror("Child   : [sem_open] Failed\n"); 
		pthread_exit(0);
	}
	
//	printf("Child Semaphore was opened ok!\n");


	while(true)
        {
		//----------------- Checking the current status of semaphore
		if (sem_getvalue(sem_id,&status) < 0)
		{
			printf("Error when get value\n");
			//std::errExit("sem_getvalue");
			exit(EXIT_FAILURE);

		}
		std::cout<<"Current semaphore: "<<status<<std::endl;
 		
		
		//----------------- Wait and block untill recieving the unlock signal from parent process
		if (sem_wait(sem_id) < 0)
        		printf("Child   : [sem_wait] Failed \n");
		
		pthread_mutex_lock(&mtx);
		printf("Captured!\n");
                
		for (uint8 ii=0;ii<SIZE;ii++)
		{
			for (uint8 jj=0;jj<SIZE;jj++)
			{ 
			 	matrix1[ii][jj] = count;
			}
		}
                count++;

                pthread_mutex_unlock(&mtx);

        }
 	pthread_exit(0);
//	return NULL;

}




		
//===================================
//		THREAD 2
//	USING TO GET VALUE FROM ARRAY
//
//===================================


void *get_arr(void* arg)
{
        int tem[SIZE][SIZE];
        while (true)
        {
                pthread_mutex_lock(&mtx);

                for (uint8 ii=0;ii<SIZE;ii++)
                        for (uint8 jj=0;jj<SIZE;jj++)
                                tem[ii][jj] = matrix1[ii][jj];

                pthread_mutex_unlock(&mtx);
                for (uint8 ii=0;ii<SIZE;ii++)
                {
                        for (uint8 jj=0;jj<SIZE;jj++)
                        {
                                printf("%d  ",tem[ii][jj]);
                        }
                        printf(" \n");
                }

        }
        pthread_exit(0);
}


//===================================
//		CHILD
//	USING TO PROCESS IMAGE
//       (CAPTURE AND PROCESS)
//===================================

void child(void)
{

	pthread_t t1,t2;		// Using to create 2 threads
//	int value1;			// Be used to check the status of semaphore


	//-------------------------- initialize the matrix
	for (uint8 i=0;i<SIZE;i++)
        {
                for (uint8 j=0;j<SIZE;j++)
                {
                        matrix1[i][j] = 0;
                }

        }


	//--------------------------- Create thread
	// THREAD
	//--------------
	
	if ( pthread_create(&t1,NULL,get_arr,NULL) != 0)
		printf("pthread_create_fail!!");

	if ( pthread_create(&t2,NULL,write_arr,NULL) != 0)
		printf("pthread_create_fail!!");


	if (pthread_join(t1, NULL) != 0)
		printf("pthread_JOIN_fail!!");

	if (pthread_join(t2, NULL) != 0)
		printf("pthread_JOIN_fail!!");

	exit(EXIT_SUCCESS);

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
