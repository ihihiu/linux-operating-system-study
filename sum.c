#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	long long sum=0;
	int i;
	int p[2];
	pipe(p);
	pid_t pid = fork();

	if(pid<0)
	{
		printf("error");
		return 1;
	}
	else if (pid == 0)
	{
		for(i=1;i<=50000;i++)
		{
			sum+=i;
		}
		write(p[1], &sum, sizeof(sum));
		return 0;
	}
	else{
		read(p[0], &sum, sizeof(sum));
		for(i=50001;i<=100000;i++)
		{
			sum+=i;
		}
		printf("sum : %lld\n", sum);
		return 0; 
	}
	return 0;
}

