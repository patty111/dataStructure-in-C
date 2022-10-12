#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack_for_int.h"
#include "stack_for_char.h"

typedef enum{lparen, rparen, plus, minus, devide, multiply, mod, eos, operand} precedence;

precedence get_symbol(char symbol){
    switch (symbol){
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '*': return multiply;
        case '/': return devide;
        case '%': return mod;
        case ' ': return eos;
        default : return operand;
    }
}

// in stack precedence
int isp(precedence symbol){
    switch (symbol){
        case lparen: return 0;
        case rparen: return 19;
        case plus: return 12;
        case minus: return 12;
        case multiply: return 13;
        case devide: return 13;
        case mod: return 13;
        case eos: return 0;
        default: return -1;
    }
} 


// in coming precedence
int icp(precedence symbol){
    switch (symbol){
        case lparen: return 20;
        case rparen: return 19;
        case plus: return 12;
        case minus: return 12;
        case multiply: return 13;
        case devide: return 13;
        case mod: return 13;
        case eos: return 0;
        default: return -1;
    }
}


int eval(char* operation){
    stack_for_int* operator = ISCreate(strlen(operation));
    for (int i=0;i<strlen(operation);i++){
        if (isdigit(operation[i])){
            ISpush(operator, operation[i] - '0');
            continue;
        }

        int a = ISpop(operator);
        int b = ISpop(operator);

        switch(operation[i]){
            case '+':
                ISpush(operator, b + a);
                break;
            case '-':
                ISpush(operator, b - a);
                break;
            case '*':
                ISpush(operator, b * a);
                break;
            case '/':
                ISpush(operator, b / a);
                break;
            case '%':
                ISpush(operator, b % a);
                break;
            }
    }
    return ISpop(operator);
}


char* infix2postfix(char* operation){
    int top = -1, index = 0;
    char* result = (char*)malloc(strlen(operation) * sizeof(char));
    stack_for_char* operator = CSCreate(strlen(operation) + 1);
    CSpush(operator,'9');

    for (int i=0;i<strlen(operation);i++){
        // printf("peek: %c\n",CSpeek(operator));
        // printf("result: %s\n",result);
        if (get_symbol(operation[i]) == operand){
            result[index++] = operation[i];
            continue;;
        }

        if (get_symbol(operation[i]) != rparen){
            // printf("icp: %d isp: %d\n",icp(operation[i]), isp(CSpeek(operator)));
            if (icp(get_symbol(operation[i])) <= isp(get_symbol(CSpeek(operator))))
                result[index++] = CSpop(operator);
            CSpush(operator, operation[i]);
        }        
        // else{
        //     while (CSpeek(operator) != lparen)
        //         result[index++] = CSpop(operator);
        //     CSpop(operator);
        // }
        // printf("%s\n",result);
    }
    while (CSsize(operator)>1) result[index++] = CSpop(operator);
    return result;
}


int main(){
    char* operation = (char*)malloc(sizeof(char));

    printf("Enter operation in Infix form: \n");
    scanf("%s",operation);
    infix2postfix(operation);
    printf("%s = %s\n",operation,infix2postfix(operation));
    
        







    return 0;
}   