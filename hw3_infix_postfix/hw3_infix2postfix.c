#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tree{
     struct Tree* leftchild;
     struct Tree* rightchild;
     char data;
}treenode;


treenode* addNode(char data){
    treenode* root = (treenode*)malloc(sizeof(treenode));
    root->data = data;
    root->leftchild = NULL;
    root->rightchild = NULL;
    return root;
}


char Cpop(char* stack, int* top){
    if (*top == -1){
        printf("stack is empty!\n");
        return '!';
    }
    char val = stack[(*top)--];
    return val;
}


void Cpush(char* stack, int* top, int maxsize, char data){
    if (*top == maxsize - 1){
        printf("stack is full!\n");
        return;
    }
    stack[++(*top)] = data;
}


char Cpeek(char* stack, int* top){
    return stack[(*top)];
}


void Npush(treenode** stack, int* top, treenode* root){
    stack[++(*top)] = root;
}


treenode* Npop(treenode** stack, int* top){
    return stack[(*top)--];
}


treenode* Npeek(treenode** stack, int* top){
    return stack[*top];
}


char* init(char* str){      // add parens at front & end, if don't add can't be able to deal with things like (a+b)*(c-d)
    char* process = (char*)malloc(sizeof(char) * (strlen(str)+2));
    strcpy(process, "(");
    char rparen[2] = ")\0";
    strcat(process, str);
    strcat(process, rparen);
    return process;
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
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}


void convert2postfix(treenode* root, int len, char** result, int* count){
    if (root){
        convert2postfix(root->leftchild, len, result, count);
        convert2postfix(root->rightchild, len, result, count);
        (*result)[(*count)++] = root->data;
    }
    (*result)[*count] = '\0';
}


void inorder(treenode* root){
    if (root){
        inorder(root->leftchild);
        printf("%c ", root->data);
        inorder(root->rightchild);
    }
}


void postorder(treenode* root){
    if (root){
        postorder(root->leftchild);
        postorder(root->rightchild);
        printf("%c ", root->data);
    }
}


void preorder(treenode* root){
    if(root){
        printf("%c ", root->data);
        preorder(root->leftchild);
        preorder(root->rightchild);
    }
}


void levelorder(treenode* root){
    int front = 0; int rear = 0;
    treenode* queue[40] = {NULL};
    queue[rear++] = root;   // enqueue

    while (1){
        root = queue[front++];  // dequeue
        if (root){
            printf("%c ", root->data);
            if (root->leftchild)
                queue[rear++] = root->leftchild;
            if (root->rightchild)
                queue[rear++] = root->rightchild;
        }
        else break;
    }
}


treenode* InfixExpressionTree(char* expression){        // return root node
    expression = init(expression);
    char* cstack = (char*)malloc(sizeof(char) * strlen(expression));
    treenode** nstack = (treenode**)malloc(sizeof(treenode*) * strlen(expression));
    treenode* Tnode;

    int t = -1; int nt = -1; int* ctop = &t; int* ntop = &nt;
    
    for (int i=0;i<strlen(expression);i++){
        if (isdigit(expression[i])){       // operands
            Tnode = addNode(expression[i]);
            Npush(nstack, ntop, Tnode);
        }

        else if ((expression[i]) == '(')      // left paren
            Cpush(cstack, ctop, sizeof(treenode), '(');

        else if (expression[i] == ')'){       // right paren
            while (Cpeek(cstack, ctop) != '('){
                Tnode = addNode(Cpop(cstack, ctop));
                Tnode->rightchild = Npop(nstack, ntop);
                Tnode->leftchild = Npop(nstack,ntop);
                Npush(nstack, ntop, Tnode);
            }
            Cpop(cstack,ctop); // no use, only for pop lparen
        }
        
        else if (isoperator(expression[i])){    // operator
            while (isp(Cpeek(cstack, ctop)) >= icp(expression[i])){
                Tnode = addNode(Cpop(cstack, ctop));
                Tnode->rightchild = Npop(nstack, ntop);
                Tnode->leftchild = Npop(nstack, ntop);
                Npush(nstack, ntop, Tnode);
            }
            Cpush(cstack, ctop, strlen(expression), expression[i]);
        }
    }
    free(cstack);
    Tnode = Npeek(nstack, ntop);
    free(nstack);
    return Tnode;
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
                if (a == 0){
                    printf("\nError, division by 0!");
                    return -2147483648;
                }
                num_stack[++top] = b / a;
                break;
            }
    }
    int ans = num_stack[top];
    free(num_stack);
    return ans;
}


int valid_input(char* expression){
    int Dflag = 0; int Aflag = 0;
    int lparen = 0; int rparen = 0;
    if (!isdigit(expression[0]) && !isoperator(expression[0]) && expression[0] != '(' && expression[0] != ')'){
        printf("%s\n", expression);
        printf("^\n");
        printf("Numbers Only!\n");
        return 0;
    }
    for (int i=1;i<strlen(expression);i++){
        // paren pairs are valid
        lparen += (expression[i-1] == '(');
        rparen += ((expression[i-1] == ')'));
        // detect unknown character
        if (!isdigit(expression[i]) && !isoperator(expression[i]) && expression[i] != '(' && expression[i] != ')'){
            printf("%s\n", expression);
            for (int j=0;j<i;j++) printf(" "); printf("^\n");
            for (int j=0;j<i;j++) printf(" "); printf("Numbers Only!\n");
            return 0;
        }
        // expression start/end with operator
        if (isoperator(expression[0]) || isoperator(expression[strlen(expression)-1])){
            printf("Expression should not start/end with operator!\n");
            return 0;
        }
        // detect continuos operand or operator or parens pairs like "()"
        if ((isoperator(expression[i]) && isoperator(expression[i-1])) || ((isdigit(expression[i]) && isdigit(expression[i-1]))) || (expression[i-1] == '(' && expression[i] == ')')){
            printf("%s\n", expression);
            for (int j=0;j<i;j++) printf(" "); printf("^\n");
            for (int j=0;j<i;j++) printf(" "); printf("Error Input!\n");
            return 0;
        }
            // printf("i:%d lparen %d / rparen %d\n",i, lparen, rparen);
    }
    lparen += expression[strlen(expression)-1] == '(';
    rparen += expression[strlen(expression)-1] == ')';

    if (lparen != rparen){
        printf("Parens do not match!");
        return 0;
    }
    return 1;
}


// 8*((4+2)/(5-3))+4/(4+(2-5))  ((a+(b-k))*((m/(n*p)+n)/(d+e)))
int main(){
    char* post = (char*)malloc(sizeof(char) * 40); char** ptrans = &post;
    while (1){
        memset(post, 0, sizeof(char)*40);  // 要重制 string
        char* expression = (char*)malloc(sizeof(char) * 40);
        printf("\nPlease enter an infix expression and press enter: "); scanf("%s",expression);
        
        if (expression[0] == 27)    // esc then quit program (esc ASCII is 27)
            break;

        if (valid_input(expression)){
            printf("The postfix expression: "); postorder(InfixExpressionTree(expression));
            printf("\nThe prefix expression:  "); preorder(InfixExpressionTree(expression));
            printf("\nThe level-order expression:  "); levelorder(InfixExpressionTree(expression));
            
            // eval using postfix
            int c = 0; int* count = &c;
            convert2postfix(InfixExpressionTree(expression), strlen(expression), ptrans, count);
            if (posteval(post) != -2147483648) // division by 0
                printf("\n= %d", posteval(post));
        }
        printf("\n--------------------------------------------------\n");
    }
    return 0;
}