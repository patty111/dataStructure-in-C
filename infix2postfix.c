#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char pop(char* stack, int* top){
    if (*top == -1){
        printf("stack is empty!\n");
        return '!';
    }
    char val = stack[(*top)--];
    return val;
}


void push(char* stack, int* top, int maxsize, char data){
    if (*top == maxsize - 1){
        printf("stack is full!\n");
        return;
    }
    stack[++(*top)] = data;
}


char peek(char* stack, int* top){
    return stack[(*top)];
}

// in stack precedence
int isp(char symbol){
    switch (symbol){
        case '(': return 0;
        case ')': return 19;
        case '+': return 12;
        case '-': return 12;
        case '*': return 13;
        case '/': return 13;
        case '\0': return 0;
        default: return -1;
    }
} 


// in coming precedence
int icp(char symbol){
    switch (symbol){
        case '(': return 20;
        case ')': return 19;
        case '+': return 12;
        case '-': return 12;
        case '*': return 13;
        case '/': return 13;
        case '\0': return 0;
        default: return -1;
    }
}


int isoperator(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
}


char* infix2postfix(char* expression){
    char* cstack = (char*)malloc(sizeof(char) * strlen(expression));
    char* result = (char*)malloc(sizeof(char) * strlen(expression));
    int t = -1; int* top = &t;

    int index = 0;
    for (int i=0;i<strlen(expression);i++){
        if (!isoperator(expression[i])){          // is operand
            result[index++] = expression[i];
            continue;
        }
        if ((expression[i]) == '(');          // left paren
        else if (expression[i] == ')'){       // right paren
            while (peek(cstack, top) != '(')
                result[index++] = pop(cstack, top);
            pop(cstack,top); // no use, only for pop lparen
            continue;
        }
        else if (icp(expression[i]) <= isp(peek(cstack, top))){    // operator
            result[index++] = pop(cstack, top);
            if (icp(expression[i]) <= isp(peek(cstack, top)))
                result[index++] = pop(cstack, top);
        }

        push(cstack, top, strlen(expression), expression[i]);
    }

    while (*top != -1)      // end of string, pop all in stack
        result[index++] = pop(cstack, top);
    
    return result;
}


int posteval(char* expression){
    int len = strlen(expression);
    int* num_stack = (int*)malloc(sizeof(int) * (len));
    int top = -1;

    for (int i=0;i<len;i++){
        if (isdigit(expression[i])){
            num_stack[++top] = expression[i] - '0';
            continue;
        }

        int a = num_stack[top--]; int b = num_stack[top--];
        switch(expression[i]){
            case '+':
                num_stack[++top] = b + a;
                break;
            case '-':
                num_stack[++top] = b - a;
                break;
            case '*':
                num_stack[++top] = b * a;
                break;
            case '/':
                num_stack[++top] = b / a;
                break;
            }
    }
    return num_stack[top];
}

int main(){
    char* expression = "8*((4+2)/(5-3))+4/(4+(2-5))";
    // char* expression = "(a+(b-k))*((m/(n*p)+n)/(d+e))";
    // int result = posteval(expression);
    
    printf("%s => %s\n", expression, infix2postfix(expression));
    // printf("%s => %s = %d\n", expression, infix2postfix(expression),result);
    // printf("%d\n", strlen(expression));
    
    return 0;	

}