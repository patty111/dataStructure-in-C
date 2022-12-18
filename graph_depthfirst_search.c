#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vertice{
    struct Vertice* next;
    int data;
}vertice;

int G[10][10],visited[10],n;    //n is no of vertices and graph is sorted in array G[10][10]

int main()
{
    int i,j;
    printf("Enter number of vertices:");
  
scanf("%d",&n);
    //read the adjecency matrix
printf("\nEnter adjecency matrix of the graph:");
  
for(i=0;i<n;i++)
       for(j=0;j<n;j++)
scanf("%d",&G[i][j]);
    //visited is initialized to zero
   for(i=0;i<n;i++)
        visited[i]=0;
    DFS(0);
}