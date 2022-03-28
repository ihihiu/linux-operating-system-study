#include <stdio.h>
#define MAX_SIZE 20

int stack[MAX_SIZE];
int top=-1;

int isEmpty() {
	if(top==-1){
	       	printf("STACK IS Empty.\n");
		return 1;
	}
	return 0;

}
int isFull() {
	if(top == MAX_SIZE-1){
		printf("STACK IS FULL.\n");
		return 1;
	}
	return 0;
}
void push(int value){
	if(!isFull())	stack[++top]=value;
}

int pop() {
	if(!isEmpty())	return stack[top--];
}

int peek(){
	if(!isEmpty())	return stack[top];
}

void display(){
	for(int i=0;i<=top;i++)
		printf("%d ",stack[i]);
	printf("\n");
}

int main(){
	for(int i=1; i<=10; i++)
		push(i);
	display();
	pop();
	pop();
	display();
	return 0;
}


