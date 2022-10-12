#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct{
    int maxsize;
    int top;
    char* element;
}stack_for_char;

// CS stands for Char Stack
stack_for_char* CSCreate(int stackSize){
    stack_for_char* newStack = (stack_for_char*)malloc(sizeof(stack_for_char));
    newStack->top = -1;
    newStack->maxsize = stackSize;
    newStack->element = (char*)malloc(sizeof(char) * stackSize);
    return newStack;
}


bool CSisEmpty(stack_for_char* Stack){
    return Stack->top == -1;
}


bool CSisFull(stack_for_char* Stack){
    return Stack->maxsize - 1 == Stack->top; 
}


// function won't be able to modify globally if it is passed by value. In this case Stack->element is value, 
// but Stack->element points to another memory location where stores an array is fine(?) (I hope i understand it right)
void CSpush(stack_for_char* Stack, char value){
    if (CSisFull(Stack)){
        printf("Stack Overflow...\n");
        return;
    }
    Stack->element[++(Stack->top)] = value; 
}


int CSsize(stack_for_char* Stack){
    return Stack->top+1;
}


char CSpeek(stack_for_char* Stack){
    return Stack->element[Stack->top];
}


char CSpop(stack_for_char* Stack){
    if (CSisEmpty(Stack)){
        printf("Stack Underflow... \n");
        return 0;
    }
    return Stack->element[Stack->top--];
}