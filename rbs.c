#include <stdio.h>
#include <stdlib.h>

void shift(unsigned char *bit, int frame_no)
{
	int i;
	for(i=0;i<frame_no;i++)
	{
		bit[i] = bit[i] >> 1;
	}
}

void display(int *arr, int frame_no, int value)
{
	int i;
	printf("%d (", value);
	for(i=0;i<frame_no;i++)
	{
		if(arr[i+1]==-1 || i==frame_no-1)
		{
			printf("%d) ", arr[i]);
			break;
		}
		else
		{
			printf("%d,",arr[i]);
		}
	}
}

int check(int *arr, int frame_no)
{
	int i;
	for(i=0;i<frame_no;i++)
	{
		if(arr[i]==-1)
		{
			return i;
		}
	}
	return -1;
}

void compare_swap(int *arr, unsigned char *bit, int frame_no, int value)
{
	int i;
	int index=0;
	int min=bit[0];
	for(i=1;i<frame_no;i++)
	{
		if(bit[i] < min)
		{
			min=bit[i];
			index=i;
		}
	}
	arr[index]=value;
	bit[index]=128;
}

void print_bit(unsigned char *bit, int frame_no)
{
	int i;
	printf("[");
	for(i=0;i<frame_no;i++)
	{
		printf("%d ", bit[i]);
	}
	printf("]\n");
}
int main(int argc, char *argv[])
{
        FILE *fp;
	int element;
        int frame_no,i, j;
        int num=0;
	int pages[100];
	int pages_no = 0;
	int *arr;
	unsigned char *bit;
	int fault=0;
	
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

        arr=(int*)malloc(sizeof(int)*frame_no);
        bit=(unsigned char*)malloc(sizeof(unsigned char)*frame_no);
	
	for(i=0;i<frame_no;i++)
	{
		arr[i]=-1;
		bit[i]=0;
	}
	
	do
	{
		int exist=0;
		for(i=0;i<frame_no;i++)
		{
			if(arr[i]==pages[num])
			{
				bit[i] |= 128;
				exist=1;
				break;
			}
		}
		if(exist)
		{
			display(arr, frame_no, pages[num]);
			printf("S\n");
			print_bit(bit, frame_no);
		}
		else
		{
			int empty_no = check(arr, frame_no);
			if(empty_no!=-1)
			{
				arr[empty_no]=pages[num];
				display(arr, frame_no, pages[num]);
				bit[empty_no] |= 128;
				printf("F\n");
				print_bit(bit, frame_no);

			}		
			else
			{
				compare_swap(arr, bit, frame_no, pages[num]);
				display(arr, frame_no, pages[num]);
				printf("F\n");
				print_bit(bit, frame_no);
			}
			fault++;

		}
		shift(bit, frame_no);
		num++;

	}while(num<pages_no);
	
	printf("Page Fault Ratio: %d/%d\n", fault, pages_no);
	free(arr);
	free(bit);	
}

