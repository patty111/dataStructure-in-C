#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tree{
     struct Tree* leftchild;
     struct Tree* rightchild;
     int data;
}tree_ptr;

void inorder(tree_ptr *ptr){
    if (ptr){
        inorder(ptr->leftchild);
        printf("%d", ptr->data);
        inorder(ptr->rightchild);
    }
}

int main(){
    





    return 0;	
}