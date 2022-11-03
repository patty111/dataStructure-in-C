#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#define MAX_TERMS 101
/*
Sample Input:
6 5
1 0 0 0 0
1 0 2 0 -1
0 3 0 0 0
0 0 1 0 0
0 0 0 0 1
0 0 0 0 0

5 3
2 1 0
0 0 0
0 3 4
0 0 0
0 1 1
*/

typedef struct Terms{
    int row;
    int col;
    int value;
}terms;

typedef struct Matrix{
    terms terms[MAX_TERMS];
}matrix;


// zero matrix
matrix blank_matrix_create(int r, int c){
    matrix M;
    M.terms[0].row = r;
    M.terms[0].col = c;
    M.terms[0].value = 0;
    return M;
}


matrix matrix_create(int r, int c){
    matrix M;
    int count = 1,tmp;
    M.terms[0].row = r;
    M.terms[0].col = c;
    
    for (int i=0;i<M.terms[0].row;i++){
        for (int j=0;j<M.terms[0].col;j++){
            if (scanf("%d",&tmp) != 0 && tmp != 0){
                M.terms[count].row = i;
                M.terms[count].col = j;
                M.terms[count].value = tmp;
                count++;
            }
        }
    }
    M.terms[0].value = count - 1;
    return M;
}


void print_matrix(matrix M){
    int flag = 1;
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
}


void print_terms(matrix M){
    printf("     | row | col |value\n");
    for (int i=0;i<M.terms[0].value+1;i++){
        printf("------------------------\n");
        printf("a[%2d]| %3d | %3d | %3d \n",i,M.terms[i].row,M.terms[i].col,M.terms[i].value);
    }printf("\n");
}


matrix fast_transpose(matrix M,int printornot){
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

    if (printornot)
        print_matrix(new_matrix);
    return new_matrix;
}


void print_submatrix(matrix M, int* r, int* c, int lenR, int lenC){
    for (int i=0;i<lenR;i++){
        for (int j=0;j<lenC;j++){
            int flag = 1;
            for (int k=1;k<=M.terms[0].value;k++){
                if (r[i] == M.terms[k].row && c[j] == M.terms[k].col){
                    printf("%d ",M.terms[k].value);
                    flag = 0;
                }
            }
            if (flag) 
                printf("0 ");
        }
        printf("\n");
    }
}


matrix matrix_multiply(matrix A, matrix B, int printornot){
    matrix C;
    int C_cursor = 0;

    B = fast_transpose(B, 0);
    C = blank_matrix_create(A.terms[0].row, B.terms[0].row);

    for (int i=1;i<=A.terms[0].value;i++){
        for (int j=1;j<=B.terms[0].value;j++){
            if (A.terms[i].col == B.terms[j].col){
                
                int flag = 1;
                for (int k=1;k<=C.terms[0].value;k++){ // 重複
                    if (C.terms[k].row == A.terms[i].row && C.terms[k].col == B.terms[j].row){
                        C.terms[k].value += A.terms[i].value * B.terms[j].value;
                        flag = 0;
                    }
                } // 不重複

                if (flag){
                    C.terms[++C_cursor].row = A.terms[i].row;
                    C.terms[C_cursor].col = B.terms[j].row;
                    C.terms[C_cursor].value = A.terms[i].value * B.terms[j].value;
                    C.terms[0].value++;
                }
            }
        }
    }
    if (printornot)
        print_matrix(C);
    return C;
}


matrix hadamard_product(matrix A, matrix B, int printornot){
    int count = 1;
    matrix result = blank_matrix_create(A.terms[0].row, A.terms[0].col);
    
    for (int i=1;i<=A.terms[0].value;i++){
        for (int j=1;j<=B.terms[0].value;j++){
            if (A.terms[i].row == B.terms[j].row && A.terms[i].col == B.terms[j].col){
                result.terms[count].value = A.terms[i].value * B.terms[j].value;
                result.terms[count].row = A.terms[i].row;
                result.terms[count++].col = A.terms[i].col;
            }
        }
    }
    result.terms[0].value = count - 1;
    if (printornot)
        print_matrix(result);
    return result;
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
        
        // list out commands and remaining matrix
        printf("\n0. Quit\n1. create matrix    2. create blank matrix\n3. fast transpose   4. matrix multiply\n5. Hadamard Product 6. get submatrix\n7. print matrix     8. print matrix terms\n9. matrix update\n");
        printf("Matrix in list: %s", cursor > -1 ? " " : "None");
        for (int i=0;i<20;i++) printf("%s ",matrix_name[i]);printf("\n> ");
        scanf("%d",&key);

        switch (key){
            case 0:
                loop = -1;
                break;


            case 1:
                printf("Enter matrix name: ");
                scanf("%s",matrix_name[++cursor]);

                printf("Enter matrix size(r c): ");
                scanf("%d %d",&r,&c);

                matrix_arr[cursor] = matrix_create(r,c);
                break;

            
            case 2:
                printf("Enter matrix name: ");
                scanf("%s",matrix_name[++cursor]);

                printf("Enter matrix size(r c): ");
                scanf("%d %d",&r,&c);

                matrix_arr[cursor] = blank_matrix_create(r,c);
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

                printf("Enter 2 matrices' name that you want to multiply(A * B = C):\n");
                scanf("%s %s",name1,name2);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);
                find2 = find_index(matrix_name,matrix_arr,name2,cursor);

                if (matrix_arr[find1].terms[0].col != matrix_arr[find2].terms[0].row){
                    printf("Matrix can't multiply\n");
                    break;
                }

                printf("Enter matrix name to store the result:\n");
                scanf("%s",matrix_name[++cursor]);

                matrix_arr[cursor] = matrix_multiply(matrix_arr[find1],matrix_arr[find2], 1);
                break;


            case 5:
                if (cursor < 1){
                    printf("Not enough Matrix...\n");
                    break;
                }

                printf("Enter 2 matrices' name to do Hadamard Product (A ⊙ B = C):\n");
                scanf("%s %s",name1,name2);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);
                find2 = find_index(matrix_name,matrix_arr,name2,cursor);

                if (matrix_arr[find1].terms[0].row != matrix_arr[find2].terms[0].row || matrix_arr[find1].terms[0].col != matrix_arr[find2].terms[0].col){
                    printf("Matrix can't do Hadamard Product...\n");
                    break;
                }

                printf("Enter matrix name to store the result:\n");
                scanf("%s",matrix_name[++cursor]);

                matrix_arr[cursor] = hadamard_product(matrix_arr[find1],matrix_arr[find2], 1);
                break;


            case 6:
                printf("Enter matrix name to find submatrix: \n");
                scanf("%s",name1);
                find1 = find_index(matrix_name, matrix_arr, name1, cursor);

                printf("Enter number of rows and columns of submatrix:\n");
                scanf("%d %d",&r,&c);
                int* subR = (int*)malloc(sizeof(int));
                int* subC = (int*)malloc(sizeof(int));

                printf("Enter subrows: ");
                for (int i=0;i<r;i++) scanf("%d",&subR[i]);

                printf("Enter subcolumns: ");
                for (int i=0;i<c;i++) scanf("%d",&subC[i]);
                
                printf("\n"); print_submatrix(matrix_arr[find1],subR , subC, r, c);
                break;


            case 7:
                printf("Enter name of matrix you want to print: \n");
                scanf("%s",name1);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);

                print_matrix(matrix_arr[find1]);
                break;


            case 8:
                printf("Enter name of matrix you want to print it's terms: \n");
                scanf("%s",name1);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);

                print_terms(matrix_arr[find1]);
                break;

            
            case 9:
                printf("Enter name of matrix to amend: ");
                scanf("%s",name1);
                find1 = find_index(matrix_name,matrix_arr,name1,cursor);
                
                printf("Enter matrix size(r c): ");
                scanf("%d %d",&r,&c);

                matrix_arr[find1] = matrix_create(r, c);
        }       
    }

    return 0;	
}