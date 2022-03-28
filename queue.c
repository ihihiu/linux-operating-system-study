#include <stdio.h>
#define MAX_SIZE 20

int front=-1;
int rear=-1;
int queue[MAX_SIZE];

int isEmpty(){
	if(front==rear){
		printf("QUEUE IS EMPTY.\n");
		return 1;
	}
		return 0;
}

int isFull(){
	if((rear+1)%MAX_SIZE==front){
		printf("QUEUE IS FULL.\n");
		return 1;
	}
	return 0;
}

void enqueue(int value){
	if(!isFull()){
		rear = (rear+1)%MAX_SIZE;
		queue[rear]=value;
	}
}

int dequeue(){
	if(!isEmpty()){
		front=(front+1)%MAX_SIZE;
		return queue[front];
		}
}
	
int peek(){
	if(!isEmpty()){
		return queue[(front+1)%MAX_SIZE];
	}
}

void display(){
	int maxi=(front < rear) ? rear : rear+MAX_SIZE;
	for(int i=front+1;i<=maxi;i++)
		printf("%d ",queue[i]);
	printf("\n");
}

int main(){
	for(int i=1; i<=10; i++)
		enqueue(i);
	display();
	dequeue();
	dequeue();
	display();
}

