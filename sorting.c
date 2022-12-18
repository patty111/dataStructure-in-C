#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct Node{
    int data;
    struct Node* next;
}node;

void printArr(int arr[],int len){
    for (int i=0;i<len;i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insertion_sort(int* arr, int len){
    /*
Take the first element and consider it to be a sorted part
Now pick arr[1] and store it as a temporary variable
Start comparing the values of tmp with elements of the sorted part from the rear side
If tmp is less than the rear element, say arr[k], then shift arr[k] to k+1 index
This shifting will continue until the appropriate location is identified. Then, we will put the temporary element at the identified location
This will continue for all the elements, and we will have our desired sorted array in ascending order    
    
    best case O(n) worst case and average case is O(n^2)
    */
        printArr(arr, len);
    for (int i=1;i<len;i++){
        int key = arr[i];
        int j = i-1;  //這邊注意是 i-1 !!!
        while (j>=0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
        printArr(arr, len);
    }
}

void insertion_with_linkedList(node* LL){
    ;
}



/*
worst case is O(n^2)
best case and average case is O(nlogn)

this is the best internal sorting method for average cases
however its a unstable method

*/
void quicksort(int arr[], int len, int left, int right){
    int i, j, pivot;
    i = left; j = right; pivot = arr[left];

    if (left < right){  // else return
        while (i < j){
            while (arr[i] <= pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i < j){
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        arr[left] = arr[j];
        arr[j] = pivot;
        printf("PIVOT: %d, ",pivot);printArr(arr,10);

        quicksort(arr, len, left, j-1);
        quicksort(arr, len, j+1, right);
    }
}


void merge(int arr[], int sorted[], int front, int mid, int end){
    int sfront = mid + 1; // index of second subtree
    int j = front; // index of sorted array

    while (front < mid && sfront < end){
        if (arr[front] <= arr[sfront])
            sorted[j++] = arr[front++];
        else
            sorted[j++] = arr[sfront++];
    }
    
}
// recursive addition
void mergesort(int arr[], int lower, int upper){ // front end 紀錄矩陣範圍
    if (lower < upper){
        int mid = (front + end)/2;
        mergesort(arr, lower, mid);
        mergesort(arr, mid, end);
        merge(arr, lower, mid, upper);
    }

}

int main(){
    // int arr1[10] = {8,7,5,6,4,2,3,1,9,0};
    int arr1[10] = {60,50,20,35,40,91,65,110,70,10};
    int arr2[11] = {8,7,5,6,4,2,10,3,1,9,0};

    node* LL = (node*)malloc(sizeof(node));
    LL->next = NULL;
    LL->data = 10;
    node* current = LL;
    for (int i=1;i<10;i++) {
        current->next = (node*)malloc(sizeof(node));
        current = current->next;
        current->data = 10-i;
        current->next = NULL;
    }
    
    // for (int i=0;i<len;i++){
    //     for (int j=0;i<len-i-1;j++){
    //         if (arr[j] > arr[j+1]){
    //             int tmp = arr[j];
    //             arr[j] = arr[j+1];
    //             arr[j+1] = tmp;
    //         }
    //     }
    // }
    printArr(arr1, 10);
    
    // insertion_sort(arr1,10);
    quicksort(arr1,10,0,9);



    return 0;	
}