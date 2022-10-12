#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct{
    int maxsize;
    int top;
    int* element;
}stack_for_int;

bool ISisFull();
bool ISisEmpty();
stack_for_int* ISCreate();
void ISpush();
int ISpop();


stack_for_int* ISCreate(int stackSize){
    stack_for_int* newStack = (stack_for_int*)malloc(sizeof(stack_for_int));
    newStack->top = -1;
    newStack->maxsize = stackSize;
    newStack->element = (int*)malloc(sizeof(int) * stackSize);
    return newStack;
}


bool ISisEmpty(stack_for_int* Stack){
    return Stack->top == -1;
}


bool ISisFull(stack_for_int* Stack){
    return Stack->maxsize - 1 == Stack->top; 
}


// function won't be able to modify globally if it is passed by value. In this case Stack->element is value, 
// but Stack->element points to another memory location where stores an array is fine(?) (I hope i understand it right)
void ISpush(stack_for_int* Stack, int value){
    if (ISisFull(Stack)){
        printf("Stack Overflow...\n");
        return;
    }
    Stack->element[++(Stack->top)] = value; 
}


int ISsize(stack_for_int* Stack){
    return Stack->top+1;
}


int ISpeek(stack_for_int* Stack){
    return Stack->element[Stack->top];
}

int ISpop(stack_for_int* Stack){
    if (ISisEmpty(Stack)){
        printf("Stack Underflow... \n");
        return 0;
    }
    return Stack->element[Stack->top--];
}