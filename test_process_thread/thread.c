#include <pthread.h>
//#include <mutex>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 10
typedef unsigned char uint8;


int matrix[SIZE][SIZE];
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *get_arr(void* arg)
{
	int tem[SIZE][SIZE];
	while (true)
	{
		pthread_mutex_lock(&mtx);
		for (uint8 ii=0;ii<SIZE;ii++)
			for (uint8 jj=0;jj<SIZE;jj++)
				tem[ii][jj] = matrix[ii][jj];
		
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
	return NULL;
}



void *write_arr(void* arg)
{
	static uint8 value = 0;
	while(true)
	{
		pthread_mutex_lock(&mtx);
		 for (uint8 ii=0;ii<SIZE;ii++)
                        for (uint8 jj=0;jj<SIZE;jj++)
                                matrix[ii][jj] = value;
		 value++;
		 
		 pthread_mutex_unlock(&mtx);

	}

	return NULL;

}



void main()
{
	pthread_t t1,t2;
	int s;
	for (uint8 i=0;i<SIZE;i++)
	{
		for (uint8 j=0;j<SIZE;j++)
		{
			matrix[i][j] = 0;
		}

	}

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
