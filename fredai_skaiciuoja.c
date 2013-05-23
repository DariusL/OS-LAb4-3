/*
 * CS170: 
 * print4.c -- forks off THREADS threads that print their ids
 */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#define THREADS 50

double Ego()
{
	double ret = 1;
	int n = (int)pthread_self();
	int i;
	for(i = 1; i <= n; i++)
		ret *= i;
	return ret;
}

void *printme(void *arg)
{
	printf("Hi.  I'm thread %d, factorial - %f\n", (int)pthread_self(), Ego());
	return NULL;
}

int main()
{
	int i;
	int vals[THREADS];
	pthread_t tid_array[THREADS];
	void *retval;
	int err;

	for (i = 0; i < THREADS; i++) 
	{
		err = pthread_create(tid_array + i,
				     NULL,
				     printme,
				     NULL);

		if(err != 0)
		{
			fprintf(stderr,"thread %d ",i);
			perror("on create");
			exit(1);
		}
			
    	}

	for (i = 0; i < THREADS; i++) 
	{

		printf("I'm %d Trying to join with thread %d\n", 
			(int)pthread_self(),(int)tid_array[i]);
    		pthread_join(tid_array[i], &retval);
    		printf("%d Joined with thread %d\n", 
			(int)pthread_self(),(int)tid_array[i]);
  	}

	return(0);
}


