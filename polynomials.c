#include <stdio.h>
#include <stdio.h>
#define MAX_degree 10
typedef struct polynomial{
    int degree; // highest exponent
    float coefficient[MAX_degree];
}poly;

void Zero(poly* Polynomial){
    for (int i=0;i<MAX_degree;i++)
        Polynomial->coefficient[i] = 0;
    Polynomial->degree = 0;
}


int main(){

    poly* polyA; poly* polyB; poly* polyC;
    int startA = 0, startB, startC, endA, endB, endC;
    Zero(polyC);
    






    return 0;
}   