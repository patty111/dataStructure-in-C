#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack{
    int maxsize;
    int top;
    int* element;
}stack;

bool isFull();
bool isEmpty();
stack* stackCreate();
void push();
int pop();



stack* stackCreate(int stackSize){
    stack* newStack = (stack*)malloc(sizeof(stack));
    newStack->top = -1;
    newStack->maxsize = stackSize;
    newStack->element = (int*)malloc(sizeof(int) * stackSize);
    return newStack;
}


bool isEmpty(stack* Stack){
    return Stack->top == -1;
}


bool isFull(stack* Stack){
    return Stack->maxsize - 1 == Stack->top; 
}


// function won't be able to modify globally if it is passed by value. In this case Stack->element is value, 
// but Stack->element points to another memory location where stores an array is fine(?) (I hope i understand it right)
void push(stack* Stack, int value){
    if (isFull(Stack)){
        printf("Stack is full... \n");
        return;
    }
    Stack->element[++(Stack->top)] = value; 
}

int main(){
    stack* a;
    a = stackCreate(10);
    push(a, 10);
    printf("%d\n",a->element[0]);






    return 0;
}   