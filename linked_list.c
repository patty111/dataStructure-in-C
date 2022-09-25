#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;  
}node;

// typedef struct Node node;
node* head; // 要宣告global 才方便操作


node* deleteNode(node* linkedList, int find){
    node* cursor = linkedList;
    node* follow = linkedList;
    if (cursor == NULL){
        printf("Not Found\n");
        return NULL;
    }
    
    if (cursor->data == find){
        linkedList = linkedList->next;
        free(cursor);
        return linkedList;
    }

    cursor = linkedList->next;
    while (cursor != NULL){
        if (cursor->data == find){
            follow->next = cursor->next;
            free(cursor);
            return linkedList;
        }
        cursor = cursor->next;
        follow = follow->next;
    }
}


node* sortList(){

}


node* addNode(node* linkedList,int insertIndex, int value){
    


}


node* updateNode(node* linkedList, int nodeIndex, int newVal){


}


int searchNodeVal(node* linkedList, int val){
    int index;
    return index;
}

void printAll(node* linkedList){
    node* cursor = linkedList;
    if (cursor == NULL)
        printf("Nothing in list...\n");
    else
        while (cursor != NULL){
            printf("%d - ",cursor->data);
            cursor = cursor->next;
        }
}


void createLinkedList(int nodeCount){
    head = (node*)malloc(sizeof(node));
    node* current;
    
    if (nodeCount == 0)
        return;

    head->data = 1;
    head->next = NULL;
    current = head;

    for (int i=1;i<nodeCount;i++){
        current->next = (node*)malloc(sizeof(node)); // 先從現有的生出下個節點
        current = current->next;                     // 把current移動，不先移動就改data改動到的是上一個(head)的值
        current->data = i+1;
        current->next = NULL; // 讓程式不會無限循環
    }
}


int main(){
    int nodeCount;

    printf("Enter how many Nodes: ");
    scanf("%d",&nodeCount);

    createLinkedList(nodeCount);

    
    printAll(head);
    printf("\n");
    head = deleteNode(head, 10);
    head = deleteNode(head, 5);
    head = deleteNode(head, 1);
    printAll(head);


// 曾經有一隻貓貓說: -=0perdfgttttttttttttttttttttttttttttttthyjjjjjjjjjuiiiiiiii 貓貓在此給我靈感www
    return 0;
}   