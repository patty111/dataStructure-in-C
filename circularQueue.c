#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN

typedef struct Queue{
    int front, rear, currentsize, size;
    int* elements;
}queue;


queue* queueCreate(int size){
    queue* newQueue = (queue*)malloc(sizeof(queue));
    newQueue->size = size;
    newQueue->currentsize = 0;
    newQueue->front = 0;
    newQueue->rear =  -1;
    newQueue->elements = (int*)malloc(sizeof(int) * size);
    return newQueue;
}


bool isEmpty(queue* Queue){
    return Queue->currentsize == 0;
}


bool isFull(queue* Queue){
    return Queue->currentsize == Queue->size;
}


int peekfront(queue* Queue){ 
    return Queue->elements[Queue->front];
}


int peekrear(queue* Queue){
    return Queue->elements[Queue->rear];
}


void enqueue(queue* Queue, int value){
    if (isFull(Queue)){
        printf("Queue Overflow...\n");
        return;
    }

    Queue->rear = (Queue->rear + 1) % Queue->size;
    Queue->elements[Queue->rear] = value;
    Queue->currentsize++;
}


int dequeue(queue* Queue){
    if (isEmpty(Queue)){
        printf("Queue Underflow...\n");
        return QUEUE_EMPTY; // macro
    }

    int data = Queue->elements[Queue->front];
    Queue->front = (Queue->front + 1) % Queue->size;
    Queue->currentsize--;
    return data;
}


void queueDestroy(queue* Queue){
    free(Queue->elements);
}


// test above functions
int main(){
    queue* a = queueCreate(8);
    int nums[8] = {3,2,0,1,7,4,6};

    for (int i=0;i<7;i++)
        enqueue(a, nums[i]);

    for (int i=0;i<7;i++)
        printf("%d-",a->elements[i]);

    printf("\n");
    printf("%d %d\n",peekfront(a),peekrear(a));
    printf("%d\n",isFull(a));
    printf("%d ",dequeue(a));
    printf("%d ",dequeue(a));
    printf("%d ",dequeue(a));
    printf("%d ",dequeue(a));
    printf("%d\n",dequeue(a));

    printf("%d %d\n",peekfront(a),peekrear(a));
    enqueue(a, 1000);
    printf("%d %d\n",peekfront(a),peekrear(a));

    return 0;
}   