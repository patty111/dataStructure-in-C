#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// Reference: https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
int main(){
    // 1D int array
    int arrsize = 5;
    int *arr = (int*)malloc(arrsize*sizeof(int));
    for (int i=0;i<arrsize;i++) 
        arr[i] = i + 1;
    
    for (int i=0;i<arrsize;i++) 
        printf("%d ",arr[i]);
    printf("\n");
    free(arr);


    // 2D int array
    int r = 3, c = 4, count = 1;
    
    int **twoD_arr = (int**)malloc(sizeof(int*) * r);
    for (int i=0;i<r;i++) 
        twoD_arr[i] = (int*)malloc(sizeof(int) * c);

    for (int i=0;i<r;i++)
        for (int j=0;j<c;j++)
            twoD_arr[i][j] = count++;

    for (int i=0;i<r;i++)
        for (int j=0;j<c;j++)
            printf("%d ",twoD_arr[i][j]);
    



    return 0;
}   