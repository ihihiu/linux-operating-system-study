#include <stdio.h>
#include <stdlib.h>
void shift(unsigned char *bit, int frame_no)	//참조 비트를 오른쪽으로 한 칸 이동하기 위한 함수
{
	int i;
	for(i=0;i<frame_no;i++)
	{
		bit[i] = bit[i] >> 1;
	}
}
void display(int *arr, int frame_no, int value)	//출력 함수
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
int check(int *arr, int frame_no)	//arr 배열에 요구 페이지가 있는지 확인, 있으면 인덱스 번호를 없으면 -1을 리턴
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
//참조 비트 중 가장 작은 값을 찾고 그 값을 요구 페이지로 바꿈
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
	bit[index]=128;	//참조 비트를 1000 0000로 초기화
}
/* //참조 비트를 확인해보기 위한 함수
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
*/
int main(int argc, char *argv[])
{
    FILE *fp;
	int element;
    int frame_no, i, j;
    int num=0;
	int pages[100];	
	int pages_no = 0;
	int *arr; //프레임 공간을 arr 배열로 만듦
	unsigned char *bit;	//참조 비트를 저장하기 위한 배열
	int fault=0;
	
    if(argc != 2)
    {
		printf("Usage: ./program file_name\n");
		return 0;
    }
	
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &frame_no);	//프레임 수
	printf("FrameNo : %d\n",frame_no);
	
	while(fscanf(fp, "%d", &element)!=EOF)
	{
		pages[pages_no]=element;	//페이지를 순서대로 저장
		pages_no++;	//페이지 총개수
	}
	
	arr=(int*)malloc(sizeof(int)*frame_no);
	bit=(unsigned char*)malloc(sizeof(unsigned char)*frame_no);
	
	for(i=0;i<frame_no;i++)
	{
		arr[i]=-1;	//페이지를 -1로 초기화
		bit[i]=0;	//참조 비트 0으로 초기화
	}
	
	do
	{
		int exist=0; //프레임(arr 배열)에 페이지가 존재하는 지를 나타내기 위한 변수
		for(i=0;i<frame_no;i++)
		{
			if(arr[i]==pages[num])	//프레임에 페이지가 존재하는 경우
			{
				bit[i] |= 128;	//참조 비트와 1000 0000를 OR 연산하여 맨 왼쪽 비트를 1로 만듦
				exist=1;
				break;
			}
		}
		if(exist)	//프레임에 페이지가 존재하는 경우
		{
			display(arr, frame_no, pages[num]);
			printf("S\n");
			//print_bit(bit, frame_no);
		}
		else	//프레임에 페이지가 존재하지 않는 경우
		{
			int empty_no = check(arr, frame_no); //프레임이 비어있는지 확인하고 비어있는 인덱스 저장
			if(empty_no!=-1)	//빈 프레임이 있는 경우
			{
				arr[empty_no]=pages[num];
				display(arr, frame_no, pages[num]);
				bit[empty_no] = 128; //참조 비트를 1000 0000로 만듦
				printf("F\n");
				//print_bit(bit, frame_no);
			}		
			else	//빈 프레임이 없는 경우
			{
				compare_swap(arr, bit, frame_no, pages[num]); //참조 비트의 값이 최소인 페이지를 내보내고 요구 페이지를 저장
				display(arr, frame_no, pages[num]);
				printf("F\n");
				//print_bit(bit, frame_no);
			}
			fault++;
		}
		shift(bit, frame_no);	//모든 참조 비트를 오른쪽으로 한 칸 이동
		num++;
	}while(num<pages_no);
	
	printf("Page Fault Ratio: %d/%d\n", fault, pages_no);
	free(arr);
	free(bit);	
}
