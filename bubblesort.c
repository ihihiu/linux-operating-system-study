#include <stdio.h>

void BubbleSort(int arr[], int len)
{
	int temp;

	for(int i = 0; i < len -1; i++)
	{
		for(int j = 0; j < (len-i)-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}

int main(void)
{
	int arr[5] = {3, 1, 4, 5, 2};
	BubbleSort(arr, sizeof(arr)/sizeof(int));
	for (int i = 0; i < 5; i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}
