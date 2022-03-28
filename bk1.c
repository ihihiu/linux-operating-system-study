#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void display(int process, int resource, int** Array)	//Matrix를 출력하기 위한 함수
{
	int i, j;
	for(i=0;i<process;i++)
        {
                printf("P%d : ",i);
                for(j=0;j<resource;j++)
                        printf("%d ", Array[i][j]);
                printf("\n");
        }
        printf("\n");
}
int main(int argc, char* argv[]){
	FILE * fp;
	int resource, process, i, j, k, l;
	int *Total, *Available;
	int **Max, **Alloc, **Need;
	int *finished_process;

	//실행 파일, 텍스트 파일 총 2개의 인자를 받아야 함
	if(argc != 2)
	{
		printf("Usage: ./program file_name\n");
		return 0;
	}
	fp = fopen(argv[1], "r");

	fscanf(fp,"%d",&resource);
	printf("System has %d types of resources : ", resource);
	
	Total = (int *)malloc(sizeof(int)*resource);		
	Available = (int *)malloc(sizeof(int)*resource);		
	for(i=0;i<resource;i++)
	{
		fscanf(fp, "%d", &Total[i]);
		printf("%d ",Total[i]);
	}
	printf("\n");
	printf("\n");
	fscanf(fp, "%d", &process);

	//(프로세스 개수) X (자원 개수) 크기의 배열 선언
	Max = (int **)malloc(process * sizeof(*Max));
        for(int i=0; i<process; i++)
                Max[i] = (int *)malloc(resource * sizeof(**Max));	
	Alloc = (int **)malloc(process * sizeof(*Alloc));
        for(int i=0; i<process; i++)
                Alloc[i] = (int *)malloc(resource * sizeof(**Alloc));  
	Need = (int **)malloc(process * sizeof(*Need));
        for(int i=0; i<process; i++)
                Need[i] = (int *)malloc(resource * sizeof(**Need));  
	for(i=0;i<process;i++)
	{
		for(j=0;j<resource;j++)
			fscanf(fp,"%d",&Max[i][j]);
		for(k=0;k<resource;k++)
			fscanf(fp,"%d",&Alloc[i][k]);
		for(l=0;l<resource;l++)
			Need[i][l]=Max[i][l]-Alloc[i][l];
	}
	fclose(fp);

	// 각 배열의 원소 출력
	printf("Max Matrix\n");
	display(process, resource, Max);
	printf("Alloc Matrix\n");
	display(process, resource, Alloc);
	printf("Need Matrix\n");
	display(process, resource, Need);
	printf("Available : ");
	for(i=0;i<resource;i++)
	{
		int sum = 0;
       		for(j=0;j<process;j++)
			sum+=Alloc[j][i];
		Available[i] = Total[i] - sum;
	       	printf("%d ", Available[i]);
	}
	printf("\n");
	printf("\n");

	int exec_num = 0;
	bool exec;
	int sequence[process];
	int while_num = 0;
	
	finished_process = (int *)malloc(sizeof(int)*process);
	for(i=0;i<process;i++)
        {
                finished_process[i]=0;
        }	
	//do while 문의 조건
	//1. 안전 상태가 되려면 while 문으로 모든 프로세스를 한 번씩 체크할 때 하나 이상의 프로세스가 무조건 실행되어야 하므로
	//실행 횟수(exec_num)는 while 문이 돈 횟수(while_num)보다 크거나 같아야 함
	//2. 모든 프로세스가 실행되어야 하므로 프로세스 개수만큼 반복문이 돌아야 함
	do{
		for(i=0;i<process;i++)
		{
			if(finished_process[i] == 0)	//실행 종료된 프로세스가 아니어야 함
			{
				exec = true;
				for(j=0;j<resource;j++)
				{
					if(Need[i][j]>Available[j])		//필요한 자원의 수가 이용 가능한 자원의 수보다 많으면 실행 불가
					{
						exec = false;
						break;
					}
				}
				if(exec)
				{
					printf("P%d : ", i);
					for(j=0;j<resource;j++)
						printf("%d ", Need[i][j]);
					printf("=> ");
					for(j=0;j<resource;j++)
					{
						Available[j] = Available[j] - Need[i][j] + Max[i][j];	//자원을 사용하고 반납 함
						Need[i][j] = 0;
						printf("%d ", Available[j]);

					}
					printf("\n");
					sequence[exec_num] = i;	//순서를 기억하기 위해 프로세스 번호 저장
					exec_num++;	//실행 횟수 증가
					finished_process[i] = 1;	//실행 완료 표시
				}
			}
		}
		while_num++;
	} while(while_num <= exec_num && exec_num < process);

	if(exec_num==process)	//안전 상태: 실행 횟수가 프로세스 개수와 같은 경우
	{
		printf("\n");
		printf("Safe sequece : ");
		for(i=0;i<process;i++)
		{
			if(i==process-1)
			{
				printf("P%d\n",sequence[i]);
				break;
			}
			printf("P%d->", sequence[i]);
		}
		printf("Safe state\n");
	}
	else	//불안전 상태
	{
		printf("No Safe Sequence\n");
		printf("Unsafe state\n");
	}

	free(Total);
	free(Available);
	free(finished_process);
	for(int i=0; i<process; i++)
       	{
	       	free(Max[i]);		               
	       	free(Alloc[i]);
		free(Need[i]);
	}
	free(Max);
	free(Alloc);
	free(Need);
}


