#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;  
}node;

// typedef struct Node node;
node* head; // 要宣告global 才方便操作


node* sortList(){

}


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

    printf("Element not found...\n");
    return linkedList;
}




int listLength(node* linkedList){
    int count = 0;
    if (linkedList == NULL)
        return 0;
    
    node* traverse = linkedList;
    while (traverse != NULL){
        count++;
        traverse = traverse->next;
    }
    return count;
}


node* addNode(node* linkedList,int insertIndex, int val){
    if (insertIndex < 0 || insertIndex >= listLength(linkedList) + 1){
        printf("Index Error\n");
        return linkedList;
    }

    node* temp = linkedList;
    node* skip;

    // 插入在最前面
    if (insertIndex == 0){  
        skip = (node*)malloc(sizeof(node));
        skip->next = temp;
        skip->data = val;
        return skip;
    }
    
    for (int i=1;i<=insertIndex;i++){
        if (i == insertIndex){
            // 插入在最後面
            if (insertIndex == listLength(linkedList)){
                temp->next = (node*)malloc(sizeof(node));
                temp = temp->next;
                temp->data = val;
                temp->next = NULL;
                return linkedList;
            }

            // 插入在中間
            skip = temp->next;
            temp->next = (node*)malloc(sizeof(node));
            temp = temp->next;
            temp->data = val;
            temp->next = skip;
            return linkedList;
        }

        temp = temp->next;
    }
}


/* 又有一隻貓貓在這邊留下了腳印 2022/9/25(日)
5rrrrrrr
fortran'''''''''''''''''''''''
}

6555555555555555555tttttttttttttttttt6
*/


node* updateNode(node* linkedList, int nodeIndex, int newVal){
    node* cursor = linkedList;
    for (int i=0;i<nodeIndex;i++)
        cursor = cursor->next;
    
    cursor->data = newVal;
    return linkedList;
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
        printf("\n");
}


void createLinkedList(int nodeCount){
    head = (node*)malloc(sizeof(node));
    node* current;
    
    if (nodeCount == 0)
        return;

    head->data = 0;
    head->next = NULL;
    current = head;

    for (int i=1;i<nodeCount;i++){
        current->next = (node*)malloc(sizeof(node)); // 先從現有的生出下個節點
        current = current->next;                     // 把current移動，不先移動就改data改動到的是上一個(head)的值
        current->data = i;
        current->next = NULL; // 讓程式不會無限循環
    }
}


int main(){
    int nodeCount;

    printf("Enter how many Nodes: ");
    scanf("%d",&nodeCount);

    createLinkedList(nodeCount);

    
    printAll(head);
    head = deleteNode(head, 10);
    printAll(head);

    head = addNode(head, 10, 11);
    printAll(head);
    head = addNode(head, 0, -1);
    printAll(head);
    updateNode(head, 0, 1000);
    printAll(head);
    printf("%d\n",listLength(head));



// 曾經有一隻貓貓說: -=0perdfgttttttttttttttttttttttttttttttthyjjjjjjjjjuiiiiiiii 貓貓在此給我靈感www
    return 0;
}   