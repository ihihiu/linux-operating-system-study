#include <stdio.h>

int main(){
  int sum;
  int i;

  for( i = 0; i <= 10 ; i++){
   sum += i;
 }

 printf("sum = %d\n", sum);
 return 0;
}
#include <stdio.h>

void swap(int * ptr1, int * ptr2)
{
	int temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

int main(void)
{
	int a = 10;
	int b = 20;
	printf("a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);
	return 0;
}


