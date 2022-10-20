#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* llink;
    struct Node* rlink;
}node_pointer;




int main(){
    int nodeCount = 5;
    node_pointer* A;
    A->data = 10;
    A->rlink = (node_pointer*)malloc(sizeof(node_pointer*));
    
    // createLinkedList(nodeCount);


    
    return 0;
}   