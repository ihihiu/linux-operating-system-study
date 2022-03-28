#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

volatile long int a=0;

int main()
{
	int i;
	a=0;

	for(i=0;i<=100000;i++)
	{
		a=a+i;
	}

	printf("%ld\n",a);
	return 0;
}
