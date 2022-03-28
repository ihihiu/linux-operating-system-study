#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main(){
	int pid, fd[2];
	char buf[5];

	if(pipe(fd)==-1) exit(-1);
	pid=fork();

	if(pid<0) exit(-1);
	else if(pid==0){
		close(fd[0]);
		write(fd[1], "Test", 5);
		close(fd[1]);
		exit(0);
	}
	else{
		close(fd[1]);
		read(fd[0], buf, 5);
		close(fd[0]);
		printf("%s\n", buf);
		exit(0);}

}

