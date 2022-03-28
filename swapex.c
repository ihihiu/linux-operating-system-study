#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	int sum;
	int n;
	int i;

	if(argc < 2){
		fprintf(stderr, "usage: %s int_number\n",argv[1]);
		exit(-1);
	}
	n=atoi(argv[1]);
	sum=0;
	for(i=0;i<n;i++){
		sum+=i;		
	}
	printf("sum of 1 to %d : %d\n",n,sum);
	return 0;
}
