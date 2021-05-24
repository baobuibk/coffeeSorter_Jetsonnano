#include <pthread.h>
#include <stdio.h>


void *access_arr(void)
{





}



void *write_arr(void)
{



}





void main()
{
	pthread_t t1,t2;
	int  size=0;
	if (pthread_create(&t1,NULL,acess_arr,size) != 0)
		errExitEN(s, "pthread_create");

	if (pthread_create(&t2,NULL,write_arr,size) != 0)
                errExitEN(s, "pthread_create");
	
	if (pthread_join(t1, NULL) != 0)
		errExitEN(s, "pthread_join");

	if (pthread_join(t2, NULL) != 0)
                errExitEN(s, "pthread_join");
	exit(EXIT_SUCCESS);

}
