#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#define MAX_TERMS 101
/*
Sample Input:
6 6
15 0 0 22 0 -15
0 11 3 0 0 0
0 0 0 -6 0 0
0 0 0 0 0 0
91 0 0 0 0 0
0 0 28 0 0 0
*/

typedef struct Terms{
    int row;
    int col;
    int value;
}terms;

typedef struct Matrix{
    terms terms[MAX_TERMS];
    int** array;
}matrix;


matrix read_matrix(matrix M){
    int count = 1;
    for (int i=0;i<M.terms[0].row;i++){
        for (int j=0;j<M.terms[0].col;j++){
            if (M.array[i][j] != 0){
                M.terms[count].row = i;
                M.terms[count].col = j;
                M.terms[count].value = M.array[i][j];
                count++;
            }
        }
    }
    M.terms[0].value = count - 1;
    return M;
}


matrix blank_matrix_create(int r, int c){
    matrix M;
    M.terms[0].row = r;
    M.terms[0].col = c;
    M.terms[0].value = 0;

    M.array = (int**)malloc(sizeof(int*) * M.terms[0].row);
    for (int i=0;i<M.terms[0].row;i++)  M.array[i] = (int*)malloc(sizeof(int) * M.terms[0].col);
    for (int i=0;i<r;i++) for(int j=0;j<c;j++) M.array[i][j] = 0;
    return M;
}


matrix matrix_create(int r, int c){
    matrix M;
    int count = 1,tmp;
    M.terms[0].row = r;
    M.terms[0].col = c;

    M.array = (int**)malloc(sizeof(int*) * M.terms[0].row);
    for (int i=0;i<M.terms[0].row;i++)  M.array[i] = (int*)malloc(sizeof(int) * M.terms[0].col);
    
    for (int i=0;i<M.terms[0].row;i++){
        for (int j=0;j<M.terms[0].col;j++){
            if (scanf("%d",&tmp) != 0 && tmp != 0){
                M.terms[count].row = i;
                M.terms[count].col = j;
                M.terms[count].value = tmp;
                count++;
            }
            M.array[i][j] = tmp;
        }
    }
    M.terms[0].value = count - 1;
    return M;
}


void print_matrix(matrix M){
    int flag = 1;
    clock_t begin = clock();
    for (int i=0;i<M.terms[0].row;i++){
        printf("[");
        for (int j=0;j<M.terms[0].col;j++){
            if (M.terms[flag].row == i && M.terms[flag].col == j)
                printf(" %3d",M.terms[flag++].value);
            else
                printf("   0");
        }
        printf(" ]\n");
    }
        clock_t end = clock();
        printf("runtime: %lf\n",(double)(end-begin)/CLOCKS_PER_SEC); printf("\n");
}


void print_terms(matrix M){
    printf("     | row | col |value\n");
    for (int i=0;i<M.terms[0].value+1;i++){
        printf("--------------------\n");
        printf("a[%2d]| %3d | %3d | %3d \n",i,M.terms[i].row,M.terms[i].col,M.terms[i].value);
    }printf("\n");
}


matrix fast_transpose(matrix M,int printornot){
    clock_t begin = clock();
    int col_count[MAX_TERMS] = {0}, index[MAX_TERMS] = {1};
    for (int i=1;i<=M.terms[0].value;i++)
        col_count[M.terms[i].col]++;

    for (int i=1;i<M.terms[0].col;i++)
        index[i] = index[i-1] + col_count[i-1];
    
    matrix new_matrix;
    new_matrix.terms[0].value = M.terms[0].value;
    new_matrix.terms[0].row = M.terms[0].col;
    new_matrix.terms[0].col = M.terms[0].row;

    for (int i=1;i<=M.terms[0].value;i++){
        new_matrix.terms[index[M.terms[i].col]].value = M.terms[i].value;
        new_matrix.terms[index[M.terms[i].col]].col = M.terms[i].row;
        new_matrix.terms[index[M.terms[i].col]].row = M.terms[i].col;
        index[M.terms[i].col]++;
    }

    clock_t end = clock();
    printf("transpose runtime: %lf\n",(double)(end-begin)/CLOCKS_PER_SEC); printf("\n");
    if (printornot) print_matrix(new_matrix);
    return new_matrix;
}


// void print_submatrix(matrix M, int* r, int* c, int lenR, int lenC){
//     for (int i=0;i<lenR;i++){
//         for (int j=0;j<lenC;j++)
//             printf("%d ",M.array[r[i]][c[j]]);
//     printf("\n");
//     }
// }


matrix matrix_multiply(matrix A, matrix B){
    matrix C;

    B = fast_transpose(B, 0);
    C = blank_matrix_create(A.terms[0].row, B.terms[0].row);

    for (int i=1;i<=A.terms[0].value;i++)
        for (int j=1;j<=B.terms[0].value;j++)
            if (A.terms[i].col == B.terms[j].col)
                C.array[A.terms[i].row][B.terms[j].row] += A.terms[i].value * B.terms[j].value;

    return read_matrix(C);
}


int find_index(char matrix_names[][20],matrix matrix_arr[20],char name[],int index){
    for (int i=0;i<=index;i++) 
        if (strcmp(matrix_names[i],name) == 0)
            return i;
    return -1;
}

int main(){
    matrix matrix_arr[20];
    char matrix_name[20][20];
    int cursor = -1, loop = 1;
    char name1[20], name2[20], name3[20];

    while (loop == 1){
        int key;
        int r,c;
        // list out remaining matrix
        printf("\nMatrix in list: ");
        // for (int i=0;i<=5;i++) printf("%s ",matrix_name[i]);
    printf("%s ",matrix_name[0]);printf("%s ",matrix_name[1]);printf("%s ",matrix_name[2]);
        
        printf("\n0. Quit\n1. create matrix    2. create blank matrix\n3. fast transpose   4. matrix multiply\n5. print matrix     6. print matrix terms\n");
        scanf("%d",&key);

        switch (key){
            case 0:
                loop = -1;
                break;
            case 1:
                printf("Enter matrix name:\n");
                scanf("%s",matrix_name[++cursor]);
                printf("Enter matrix size(r c):");
                scanf("%d %d",&r,&c);
                matrix_arr[cursor] = matrix_create(r,c);
                break;
            
            case 2:
                break;
            
            case 3:
                printf("Transpose which matrix? (Enter matrix name): \n");
                scanf("%s",name1);
                int find1 = find_index(matrix_name,matrix_arr,name1,cursor);
                int find2;
                matrix_arr[find1] = fast_transpose(matrix_arr[find1], 1);
                break;

            case 4:
                if (cursor < 1){
                    printf("Not enough Matrix...\n");
                    break;
                }
                printf("Enter 2 matrices name you want to multiply(A * B = C):\n");
                scanf("%s %s",name1,name2);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);
                find2 = find_index(matrix_name,matrix_arr,name2,cursor);
                if (matrix_arr[find1].terms[0].col != matrix_arr[find2].terms[0].row){
                    printf("Matrix can't multiply\n");
                    break;
                }

                printf("Enter matrix name to store the result:\n");
                scanf("%s",matrix_name[++cursor]);
                matrix_arr[cursor] = matrix_multiply(matrix_arr[find1],matrix_arr[find2]);
                break;

            case 5:
                printf("Enter name of matrix you want to print: \n");
                scanf("%s",name1);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);
                print_matrix(matrix_arr[find1]);
                break;

            case 6:
                printf("Enter name of matrix you want to print its terms: \n");
                scanf("%s",name1);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);
                print_terms(matrix_arr[find1]);
                break;
        }       
    }

    // printf("Enter size of matrix(row and column):\n");
    // int r ,c;
    // scanf("%d %d",&r, &c);
    // A = matrix_create(r,c);

    // printf("Enter size of matrix(row and column):\n");
    // scanf("%d %d",&r, &c);
    // B = matrix_create(r,c);
    // // print_terms(fast_transpose(B));
    // // print_matrix(A);
    // // print_matrix(B);
    // // print_matrix(fast_transpose(B));

    // // print_terms(A); 
    // // print_terms(fast_transpose(B)); 

    // result = matrix_multiply(A,B);
    // print_matrix(result);
    // print_terms(result);

    return 0;	
}

