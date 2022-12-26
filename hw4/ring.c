#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct adj_list_node{
    int num;
    struct adj_list_node* next;
}adj_node;

typedef struct adjList{
    adj_node* headNode;    
}adjlist;

typedef struct Graph{
    int num_of_vertices;
    adjlist* array;
}graph;


void printGraph(graph* Graph){
    for (int i=0;i<Graph->num_of_vertices;i++){
        adj_node* cursor = Graph->array[i].headNode;
        for(;cursor;cursor=cursor->next)
            printf("->%d", cursor->num);
        printf("\n");
    }
    printf("------------\n");
}


adj_node* addNode(int num){
    adj_node* newNode = (adj_node*)malloc(sizeof(adj_node));
    newNode->next = NULL;
    newNode->num = num;
    return newNode;
}


graph* createGraph(int vertices){
    graph* newGragh = (graph*)malloc(sizeof(graph));
    newGragh->num_of_vertices = vertices;
    newGragh->array = (adjlist*)malloc(sizeof(adjlist) * vertices);
    for (int i=0;i<vertices;i++)
        newGragh->array[i].headNode = addNode(i+1);
    return newGragh;
}


void addEdge(graph* Graph,int v1, int v2){
    //v1->v2
    // adj_node* newnode = addNode(v2);
    adj_node* newNode = addNode(v2);
    adj_node* tmp_node = Graph->array[v1-1].headNode;
    while (tmp_node->next)
        tmp_node = tmp_node->next;
    tmp_node->next = newNode;
    printGraph(Graph);
    
    //v2->v1
    newNode = addNode(v1);
    tmp_node = Graph->array[v2-1].headNode;
    while (tmp_node->next)
        tmp_node = tmp_node->next;
    tmp_node->next = newNode;
    printGraph(Graph);
}


int connect_components(graph* g){
    int count = 0;
    int yes[g->num_of_vertices];
    for (int i = 0;i<g->num_of_vertices;i++)
        yes[i] = 0;
    adj_node* cursor = g->array[0].headNode;
    // yes[0] = 1;

    while (cursor){
        if (yes[cursor->num-1] == 0){
            yes[(cursor->num)-1] == 1;
            cursor = g->array[(cursor->num)-1].headNode;
        }
        else{
            while (cursor->next && yes[(cursor->next->num)-1] == 1){
                cursor = cursor->next;

            }
        }
    }   
    



    return count;
}


int main(){
    int m,n;
    // scnaf("%d %d",&n, &m);  // n is 所需要的扣環數， m 扣環組合中已存在的扣環連結數
    // for (int i=0;i<m;i++){
    // }
    int V = 5;
	graph* g = createGraph(V);
    addEdge(g,1,2);
    addEdge(g,2,3);
    addEdge(g,3,4);
    addEdge(g,4,5);
    // printGraph(g);



    return 0;
}