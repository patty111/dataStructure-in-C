#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tree{
     struct Tree* leftchild;
     struct Tree* rightchild;
     int data;
}treenode;


treenode* addNode(int data){
    treenode* node = (treenode*)malloc(sizeof(treenode));
    node->data = data;
    node->leftchild = NULL;
    node->rightchild = NULL;
    return node;
}


void inorder(treenode *ptr){
    if (ptr){
        inorder(ptr->leftchild);
        printf("%d ", ptr->data);
        inorder(ptr->rightchild);
    }
}


void postorder(treenode *ptr){
    if (ptr){
        inorder(ptr->leftchild);
        inorder(ptr->rightchild);
        printf("%d ", ptr->data);
    }
}


void preorder(treenode *ptr){
    if (ptr){
        printf("%d ", ptr->data);
        inorder(ptr->leftchild);
        inorder(ptr->rightchild);
    }
}


int main(){
    treenode* tree = (treenode*)malloc(sizeof(treenode));
    tree = addNode(1);
    tree->leftchild = addNode(2);
    tree->leftchild->leftchild = addNode(4);
    tree->leftchild->rightchild = addNode(5);

    tree->rightchild = addNode(3);
    tree->rightchild->leftchild = addNode(6);
    tree->rightchild->rightchild = addNode(7);

    preorder(tree);
    printf("\n");
    printf("\n");
    inorder(tree);

    /*
          1
       2    3
      4 5  6 7

    */






    return 0;	
}