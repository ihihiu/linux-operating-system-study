#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main()
{
	int pid;

	pid=fork();

	if(pid<0) {printf("Error");
		exit(-1);}
	else if(pid==0) {printf("Child");
		exit(0);}
	else {printf("Parent");
		exit(0);}
}
