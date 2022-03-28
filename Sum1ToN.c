#include <stdio.h>

int main(void)
{
	int sum=0;
	int n;

	printf("n : ");
	scanf("%d", &n);

	for(int i=0;i<=n;i++)
	{
		sum+=i;
	}

	printf("Sum of 1 to %d : %d\n",n,sum);
	return 0;
}
