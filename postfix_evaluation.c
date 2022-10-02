#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef enum{lparen, rparen, plus, minus, devide, multiply, mod}precedence;

int eval(char* operation){
    stack* regi = stackCreate(strlen(operation));

    for (int i=0;i<strlen(operation);i++){
        if (isdigit(operation[i])){
            push(regi, operation[i] - '0');
            continue;
        }

        int a = pop(regi);
        int b = pop(regi);
        int parenflag = 0;

        switch(operation[i]){
            case '+':
                push(regi, b + a);
                break;
            case '-':
                push(regi, b - a);
                break;
            case '*':
                push(regi, b * a);
                break;
            case '/':
                push(regi, b / a);
                break;
            case '%':
                push(regi, b % a);
                break;
            }
    }
    return pop(regi);
}

int main(){
    char* operation = (char*)malloc(sizeof(char));

    printf("Enter operation in Infix form: \n");
    scanf("%s",operation);

    int cursor = 0;
    
        
    printf("%s\n",operation);
    printf("%d\n",eval(operation));






    return 0;
}   