#include <stdio.h>
#include <stdlib.h>

void shift(int **arr, int frame_no)
{
	int i;
	for(i=0;i<frame_no;i++)
	{
		arr[1][i] >> 1;
	}
}

void display(int **arr, int frame_no, int value)
{
	int i;
	printf("%d (", value);
	for(i=0;i<frame_no;i++)
	{
		if(arr[0][i+1]==-1 || i==frame_no-1)
		{
			printf("%d) ", arr[0][i]);
			break;
		}
		else
		{
			printf("%d,",arr[0][i]);
		}
	}
}

int check(int **arr, int frame_no)
{
	int i;
	for(i=0;i<frame_no;i++)
	{
		if(arr[0][i]==-1)
		{
			return i;
		}
	}
	return -1;
}

void compare_swap(int **arr, int frame_no, int value)
{
	int i;
	int index=0;
	int min_value = arr[0][0];
	for(i=1;i<frame_no;i++)
	{
		if(arr[0][i] < min_value)
		{
			min_value=arr[0][i];
			index=i;
		}
	}
	arr[0][index]=value;
	arr[1][index]=0b00000000;
}

void print_bit(int **arr, int frame_no)
{
	int i;
	for(i=0;i<frame_no;i++)
	{
		printf("%d, ", arr[1][i]);
	}
	printf("\n");
}
int main(int argc, char *argv[])
{
        FILE *fp;
	int element;
        int frame_no,i, j;
        int num=0;
	int pages[100];
	int pages_no = 0;
	int **arr;
	int hit=0;
	
        if(argc != 2)
        {
                printf("Usage: ./program file_name\n");
                return 0;
        }

        fp = fopen(argv[1], "r");

        fscanf(fp, "%d", &frame_no);
        printf("FrameNo : %d\n",frame_no);
	
	while(fscanf(fp, "%d", &element)!=EOF)
	{
		pages[pages_no]=element;
		pages_no++;
	}

        arr=(int**)malloc(sizeof(int*)*2);
      
      	for(i=0;i<2;i++)
        {
                arr[i]=(int*)malloc(sizeof(int)*frame_no);
        }
	for(i=0;i<frame_no;i++)
	{
		arr[0][i]=-1;
		arr[1][i]==0b00000000;
	}
	
	do
	{
		int exist=0;
		for(i=0;i<frame_no;i++)
		{
			if(arr[0][i]==pages[num])
			{
				hit++;
				arr[1][i] |= 128;
				exist=1;
				break;
			}
		}
		if(exist)
		{
			display(arr, frame_no, pages[num]);
			shift(arr,frame_no);
			printf("S\n");
			print_bit(arr, frame_no);
		}
		else
		{
			int empty_no = check(arr, frame_no);
			if(empty_no!=-1)
			{
				arr[0][empty_no]=pages[num];
				display(arr, frame_no, pages[num]);
				printf("F\n");
				print_bit(arr, frame_no);
			}		
			else
			{
				compare_swap(arr, frame_no, pages[num]);
				display(arr, frame_no, pages[num]);
				printf("F\n");
				print_bit(arr, frame_no);
			}

		}
		num++;

	}while(num<pages_no);

	for(i=0; i<2; i++)
		free(arr[i]);		               
	       	
}

