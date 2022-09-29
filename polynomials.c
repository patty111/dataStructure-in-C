#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_degree 101
#define MAX_TERMS 100

// Implementation of Polynomial Additions;
// This implementation stores both Polynomial A , B and result in an 1D array 

// A->expo Ａ會是記憶體位置，箭頭指向其他東西． A.expo 是指向值

typedef struct Poly{
    int start;
    int finish;
}polynomial;

typedef struct terms{
    int coeff;
    int expo;
}terms;

int avail = 0;


int coeff(polynomial poly, terms* Terms, int expo){
    for (int i=poly.start;i<=poly.finish;i++){
        if (Terms[i].expo == expo)
            return Terms[i].coeff;
    }  
    return 0;
}


terms* polyInput(polynomial poly, terms* Terms){
    poly.start = avail;
    while (1){
        scanf("%d %d", &Terms[avail].coeff, &Terms[avail].expo);
        if (Terms[avail].expo == 0 && Terms[avail].coeff == 0){
            poly.finish = avail - 1;
            return Terms;
        }
        avail++;
    }
}

// polynomial add
terms* padd(polynomial A, polynomial B, polynomial C, terms* Terms){
    


}


void printPoly(polynomial poly, terms* Terms){
    printf("%dx^%d",Terms[poly.start].coeff, Terms[poly.start].expo);
    for (int i=poly.start+1;i<=poly.finish;i++){
        if (Terms[i].coeff < 0) 
            printf(" - %dx^%d", Terms[i].coeff * -1, Terms[i].expo);
        else 
            printf(" + %dx^%d", Terms[i].coeff, Terms[i].expo);
       
    } printf("\n");
}


int main(){
    polynomial A, B, C;
    A.start = 0;
    terms* Terms = (terms*)malloc(sizeof(terms));
    // 這個malloc 我沒有乘, 但後面的scanf我用 Terms[avail] 配合avail++ 直接指派給後面的記憶體了，所以才沒問題

    printf("Enter coeffiecients and exponents of Polynomail A:\n");
    while (1){
        scanf("%d %d", &Terms[avail].coeff, &Terms[avail].expo);
        if (Terms[avail].expo == 0 && Terms[avail].coeff == 0){
            A.finish = avail - 1;
            break;
        }
        avail++;
    }

    B.start = avail;
    
    printf("Enter coeffiecients and exponents of Polynomail B:\n");
    while (1){
        scanf("%d %d", &Terms[avail].coeff, &Terms[avail].expo);
        if (Terms[avail].expo == 0 && Terms[avail].coeff == 0){
            B.finish = avail - 1;
            break;
        }
        avail++;
    }
    
    printf("RESULTS:\n");
    printPoly(A,Terms);
    printPoly(B,Terms);
    // printf("%d %d %d %d",A,start,A.finish,B.start,B.finish);
    printf("\n%d",coeff(A,Terms,4));



    return 0;
}   