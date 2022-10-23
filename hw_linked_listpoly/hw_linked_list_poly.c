#include <stdio.h>
#include <stdlib.h>
#define getName(var)

typedef struct Node{
    int expo;
    int coeff;
    struct Node *next;
}node;


int islast(node** polyterm){
    return (*polyterm)->coeff == 0 && (*polyterm)->expo == 0;
}


int compare(node* term1, node* term2){
    if (islast(&term1) || islast(&term2))
        return islast(&term1) * -1 + islast(&term2) * 1;
    return (term1->expo > term2->expo) * 1 + (term1->expo == term2->expo) * 0 + (term1->expo < term2->expo) * -1; 
    // return islast(&term1) || islast(&term2) ? (islast(&term1) * -1 + islast(&term2) * 1) : ((term1->expo > term2->expo) * 1 + (term1->expo == term2->expo) * 0 + (term1->expo < term2->expo) * -1);
}


void sortPoly(node** poly){
    node* tempnode = *poly;
    node* last = *poly;
    while (!islast(&last))
        last = last->next;

    while (!islast(&tempnode)){
        node* tempsort = *poly;
        while (!islast(&(tempsort->next))){
            if (tempsort->expo > tempsort->next->expo){
                int tempval = tempsort->expo;
                tempsort->expo = tempsort->next->expo;
                tempsort->next->expo = tempval;
                int tempcoeff = tempsort->coeff;
                tempsort->coeff = tempsort->next->coeff;
                tempsort->next->coeff = tempcoeff;
            }
            tempsort = tempsort->next;
        }
        tempnode = tempnode->next;
    }

    // reverse (convert to descending order)
    node* cursor = *poly;
    node* middle = last;
    while (!islast(&cursor)){
        last = middle;
        middle = cursor;
        cursor = cursor->next;
        middle->next = last;
    }
    cursor->next = middle;
    *poly = middle;
}


node** blankPoly(node** poly){
    poly = (node**)malloc(sizeof(node*));
    *poly = (node*)malloc(sizeof(node));
    (*poly)->expo = 0;
    (*poly)->coeff = 0;
    (*poly)->next = *poly;
    return poly;
}


void readPoly(node** poly){
    *poly = (node*)malloc(sizeof(node));
    (*poly)->next = NULL;
    node* current = *poly;
    
    while(1){
        scanf("%d %d", &current->coeff, &current->expo);
        if (islast(&current))
            break;

        current->next = (node*)malloc(sizeof(node));
        current = current->next;
        current->next = NULL;
    }
    current->next = *poly;
}


int polyLength(node** poly){
    int count = 0;
    if (poly == NULL)
        return 0;
    
    node* cursor = *poly;
    while (!islast(&cursor)){
        count++;
        cursor = cursor->next;
    }
    return count;
}


void printPoly(node** poly){
    node* cursor = *poly;
    if (!polyLength(&cursor)){
        printf("0\n");
        return;
    }

    printf("%dx^%d", cursor->coeff, cursor->expo);
    cursor = cursor->next;

    while(!islast(&cursor)){
        // 為了美化格式
        if (cursor->coeff < 0) 
            printf(" - %dx^%d", cursor->coeff * -1, cursor->expo);
        else 
            printf(" + %dx^%d", cursor->coeff, cursor->expo);
        cursor = cursor->next;
    }
    printf("\n");
}


void attach(node** poly, int coeff, int expo){
    if (islast(poly))
        (*poly)->next = *poly;
    node* cursor = (*poly)->next;
    node* follow = *poly;
    node* temp = (node*)malloc(sizeof(node));

    
    //最前面
    int flag = 0;
    if (expo >= follow->expo){
        temp->coeff = coeff;
        temp->expo = expo;
        temp->next = follow;
        flag = 1;
    }

    // 插入在中間並讓cursor指向end
    while (!islast(&follow)){
        if (follow->expo == expo)
            follow->coeff += coeff;
        else if ((follow->expo > expo && expo > cursor->expo) || (islast(&cursor) && expo < follow->expo)){
            temp->coeff = coeff;
            temp->expo = expo;
            follow->next = temp;
            temp->next = cursor;
        }
        follow = cursor;
        cursor = cursor->next;
    }

    // 指回最高次方項(head)
    if (flag){
        follow->next = temp;
        *poly = temp;
    }
    else follow->next = *poly;
}


int coeff(node** poly, int expo){
    node* cursor = *poly;
    while (!islast(&cursor)){
        if (expo == cursor->expo)
            return cursor->coeff;
        cursor = cursor->next;
    }
    return 0;
}



void erase(node** poly){
    while((*poly)->coeff != 0 && (*poly)->expo != 0){
        node* temp = *poly;
        free(temp);
        *poly = (*poly)->next;   
    }
    free(*poly);
}



void detach(node** poly, int expo){
    node* cursor = *poly;
    node* temp = (node*)malloc(sizeof(node));
    node* follow = temp;
    int count = 0;

    // while (cursor->expo != expo){
    //     follow = cursor;
    //     cursor = cursor->next;
    //     count++;
    // }

    // if (count == polyLength(&poly)-1)

    if (cursor->expo == expo){   // 第一個
        temp = cursor;
        // free
    }

    while (!islast(&cursor)){
        follow = cursor;
        cursor = cursor->next;
        if (cursor->expo == expo){
            temp = cursor;
            follow->next = cursor->next;
            // continue;
        }
        free(temp);
        
    }


    return ;
}


node** padd(node** P1, node** P2){
    int sum = 0;
    node** resultPoly = blankPoly(resultPoly);
    node* cursor1 = *P1;
    node* cursor2 = *P2;

    while (!islast(&cursor1) || !islast(&cursor2)){
        switch (compare(cursor1, cursor2)){
            case 1:
                attach(resultPoly, cursor1->coeff, cursor1->expo);
                cursor1 = cursor1->next;
                break;        
                
            case 0:
                sum = cursor1->coeff + cursor2->coeff;
                if (sum)
                    attach(resultPoly, sum, cursor1->expo);
                cursor1 = cursor1->next;
                cursor2 = cursor2->next;
                break;

            case -1:
                attach(resultPoly, cursor2->coeff, cursor2->expo);
                cursor2 = cursor2->next;
                break;
        }
    }
    return resultPoly;
}


node** psub(node** P1, node** P2){
    int sub = 0;
    node** resultPoly = blankPoly(resultPoly);
    node* cursor1 = *P1;
    node* cursor2 = *P2;

    while (!islast(&cursor1) || !islast(&cursor2)){
        switch (compare(cursor1, cursor2)){
            case 1:
                attach(resultPoly, cursor1->coeff, cursor1->expo);
                cursor1 = cursor1->next;
                break;        
                
            case 0:
                sub = cursor1->coeff - cursor2->coeff;
                if (sub)
                    attach(resultPoly, sub, cursor1->expo);
                cursor1 = cursor1->next;
                cursor2 = cursor2->next;
                break;

            case -1:
                attach(resultPoly, -1 * cursor2->coeff, cursor2->expo);
                cursor2 = cursor2->next;
                break;
        }
    }
    return resultPoly;
}


node** pmult(node** P1, node** P2){
    node* cursor1 = *P1;
    node* cursor2 = *P2;
    node** resultPoly = blankPoly(resultPoly);

    int mult;
    while (!islast(&cursor1)){
        while (!islast(&cursor2)){
            // if (cursor1->coeff * cursor2->coeff != 0)
                attach(resultPoly, cursor1->coeff * cursor2->coeff, cursor1->expo + cursor2->expo);
            cursor2 = cursor2->next;
            printPoly(resultPoly);
        }
        cursor2 = *P2;
        cursor1 = cursor1->next;
    }
    sortPoly(resultPoly);
    return resultPoly;
}




int main(){
    node** P1 = blankPoly(P1);
    node** P2 = blankPoly(P2);
    node** P3 = blankPoly(P3);
    // printf("Enter coeffiecients and exponents of Polynomial1 from the highset term:\n");
    readPoly(P1); 
    // printf("Enter coeffiecients and exponents of Polynomial2 from the highset term:\n");
    readPoly(P2);
    printPoly(P1);
    printPoly(P2);
    P3 = pmult(P1,P2);
    printPoly(P3);



    return 0;	
}


