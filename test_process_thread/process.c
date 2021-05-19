#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


const char *semName = "abc";




//------------------------------------PARENT
void parent(void)
{
	sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);
	if (sem_id == SEM_FAILED)
	{
		perror("Parent   : [sem_open] Failed\n"); 
		return;
	}
	printf("Parent: Wait for Child to Print\n");
	if (sem_wait(sem_id) < 0)
		printf("Parent: [sem_wait] Failed\n");
	printf("Parent: Child Printed! \n");


	if (sem_close(sem_id) !=0)
	{
		perror("Parent  : [sem_close] Failed\n"); 
		return;
	}
	
	if (sem_unlink(semName) < 0)
	{
		printf("Parent  : [sem_unlink] Failed\n"); 
		return;
	}

	
}


//-------------------------------------CHILD
void child(void)
{
	sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);
	if (sem_id == SEM_FAILED)
	{
		perror("Child   : [sem_open] Failed\n"); 
		return;
	}
	
	printf("Child   : I am done! Release Semaphore\n");
    	if (sem_post(sem_id) < 0)
        	printf("Child   : [sem_post] Failed \n");
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
