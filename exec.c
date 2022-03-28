#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void main()
{
	int pid;
	
	pid=fork();

	if(pid<0) {printf("Error");
		exit(-1);}
	else if(pid==0) {
		execlp("ls", "ls", "-al", NULL);
		exit(0);}
	else {wait(NULL);
		printf("ls -al Terminated");
		exit(0);}
}
