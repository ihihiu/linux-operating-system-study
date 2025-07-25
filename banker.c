#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void display(int process, int resource, int Array[process][resource])
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

	if(argc != 2)
	{
		printf("Usage: ./program file_name\n");
		return 0;
	}

	fp = fopen(argv[1], "r");
	
	if(fp==NULL)
	{
		printf("FILE ERROR");
	}
	fscanf(fp,"%d",&resource);

	printf("System has %d types of resources : ", resource);

	int Total[resource], Available[resource];

	for(i=0;i<resource;i++)
		fscanf(fp, "%d", &Total[i]);
	for(i=0;i<resource;i++)
	{
		printf("%d ",Total[i]);
	}
	printf("\n");
	printf("\n");

	fscanf(fp, "%d", &process);
	
	int Max[process][resource], Alloc[process][resource], Need[process][resource];

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

	int finished_process[process];

	for(i=0;i<process;i++)
	{
		finished_process[i]=0;
	}


	int exec_num = 0;
	bool exec;
	int sequence[process];
	int while_num = 0;

	do{
		for(i=0;i<process;i++)
		{
			if(finished_process[i] == 0)
			{
				exec = true;
				for(j=0;j<resource;j++)
				{
					if(Need[i][j]>Available[j])
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
						Available[j] = Available[j] - Need[i][j] + Max[i][j];
						Need[i][j]=0;
						printf("%d ", Available[j]);
	
					}
					printf("\n");
					sequence[exec_num] = i;
					exec_num++;
					finished_process[i] = 1;
				}
			}
		}
		while_num++;
	} while(while_num <= exec && exec_num < process);
	
	if(exec_num==process)
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
	else
	{
		printf("No Safe Sequence\n");
		printf("Unsafe state\n");
	}

}

