#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}node;


node* createLinkedList(node* linkedList, int nodecount){
    if (nodecount == 0)
        return -1;
    
    linkedList = (node*)malloc(sizeof(node));
    linkedList->next = NULL;
    linkedList->data = 0;

    node* current = linkedList;
    
    for (int i=1;i<nodecount;i++){
        current->next = (node*)malloc(sizeof(node));
        current = current->next;
        current->next = NULL;
        current->data = i;
    }

    current->next = linkedList;
    return linkedList;
}


void printList(node* linkedList){
    node* cursor = linkedList;
  
    while(1){
        printf("%d - ",cursor->data);
        cursor = cursor->next;

        if (cursor == linkedList){
            printf("\n");
            break;
        }
    }
}


int listLength(node* linkedList){
    int count = 0;
    if (linkedList == NULL)
        return 0;
    
    node* traverse = linkedList;
    while (1){
        count++;
        traverse = traverse->next;
        if (traverse == linkedList)
            break;
    }
    return count;
}


node* addNode(node* linkedList,int insertIndex, int val){
    if (insertIndex < 0 || insertIndex >= listLength(linkedList) + 1){
        printf("Index Error\n");
        return linkedList;
    }

    node* cursor = linkedList;
    node* skip;

    // 插入在最前面
    if (insertIndex == 0){
        skip = (node*)malloc(sizeof(node));
        skip->next = cursor;
        skip->data = val;

        // 讓尾端串回頭
        for (int i=0;i<listLength(linkedList)-1;i++)
            cursor = cursor->next;

        cursor->next = skip;
        return skip;
    }

    for (int i=1;i<=insertIndex;i++){
        if (i == insertIndex){
            // 插入在最後面
            if (insertIndex == listLength(linkedList)){
                cursor->next = (node*)malloc(sizeof(node));
                cursor = cursor->next;
                cursor->data = val;
                cursor->next = linkedList;
                break;
            }

            // 插入在中間
            skip = cursor->next;
            cursor->next = (node*)malloc(sizeof(node));
            cursor = cursor->next;
            cursor->data = val;
            cursor->next = skip;
            break;
        }
        cursor = cursor->next;
    }

    return linkedList;
}


node* deleteNode(node* linkedList, int find){
    node* cursor = linkedList;
    node* follow = linkedList;
    if (cursor == NULL){
        printf("Not Found\n");
        return NULL;
    }
    
    // find 在第一個
    if (cursor->data == find){
        linkedList = linkedList->next;
        free(cursor);
        return linkedList;
    }

    cursor = linkedList->next;
    while (cursor != linkedList){
        if (cursor->data == find){
            follow->next = cursor->next;
            free(cursor);
            return linkedList;
        }

        cursor = cursor->next;
        follow = follow->next;
    }

    printf("Element not found...\n");
    return linkedList;
}



int main(){
    node* head;
    head = createLinkedList(head,10);
    printList(head);
    head = addNode(head, 10, 333);
    printList(head);




    return 0;	
}