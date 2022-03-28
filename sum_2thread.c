#include<unistd.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h> 

volatile long int a=0;
pthread_mutex_t aLock;

void threadFunc1()
{
	int i;

	for(i=0;i<50000;i++)
	{
		pthread_mutex_lock(&aLock);
		a=a+i;
		pthread_mutex_unlock(&aLock);
	}
}

void threadFunc2()
{
	int i;

	for(i=50000;i<=100000;i++)
	{
		pthread_mutex_lock(&aLock);
		a=a+i;
		pthread_mutex_unlock(&aLock);
	}
}

int main(){
	pthread_t th_one, th_two;
	int i;
	a=0;

	pthread_create(&th_one, NULL, (void*)&threadFunc1,NULL);
	pthread_create(&th_two, NULL, (void*)&threadFunc2,NULL);
	
	pthread_join(th_one,NULL);
	pthread_join(th_two,NULL);

	printf("%ld\n",a);
	return 0;
}
