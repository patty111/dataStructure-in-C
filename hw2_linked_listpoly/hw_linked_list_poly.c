#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int expo;
    double coeff;
    struct Node *next;
}node;

node** P1;node** P2;node** P3;

node** blankPoly(node** poly){
    poly = (node**)malloc(sizeof(node*));
    *poly = (node*)malloc(sizeof(node));
    (*poly)->expo = 0;
    (*poly)->coeff = 0;
    (*poly)->next = *poly;
    return poly;
}


int islast(node** polyterm){
    return (*polyterm)->coeff == 0 && (*polyterm)->expo == 0;
}


int compare(node* term1, node* term2){
    if (islast(&term1) || islast(&term2))
        return islast(&term1) * -1 + islast(&term2) * 1;
    return (term1->expo > term2->expo) * 1 + (term1->expo == term2->expo) * 0 + (term1->expo < term2->expo) * -1; 
    // return islast(&term1) || islast(&term2) ? (islast(&term1) * -1 + islast(&term2) * 1) : ((term1->expo > term2->expo) * 1 + (term1->expo == term2->expo) * 0 + (term1->expo < term2->expo) * -1);
}


int degree(node** poly){
    node* tmp = *poly;
    if (islast(poly))
        return 0;
    int degree = -2147483648;
    while (!islast(&tmp)){
        degree = degree < tmp->expo ? tmp->expo : degree;
        tmp = tmp->next;
    }return degree;
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


void readPoly(node** poly){
    *poly = (node*)malloc(sizeof(node));
    (*poly)->next = NULL;
    node* current = *poly;
    
    while(1){
        scanf("%lf %d", &current->coeff, &current->expo);
        if (islast(&current))
            break;

        current->next = (node*)malloc(sizeof(node));
        current = current->next;
        current->next = *poly;
    }
}


void printPoly(node** poly, int crlf){
    node* cursor = *poly;
    if (islast(&cursor)){
        printf("0\n");
        return;
    }
    
    if (cursor->coeff - (int)cursor->coeff > 0)
        printf("%lfx^%d", cursor->coeff, cursor->expo);
    else
        printf("%.0lfx^%d", cursor->coeff, cursor->expo);
    cursor = cursor->next;

    while(!islast(&cursor)){
        if (cursor->coeff - (int)cursor->coeff == 0){
        // 為了美化格式
            if (cursor->coeff < 0) 
                printf(" - %.0lfx^%d", cursor->coeff * -1, cursor->expo);
            else 
                printf(" + %.0lfx^%d", cursor->coeff, cursor->expo);
        }
        else{
            if (cursor->coeff < 0) 
                printf(" - %lfx^%d", cursor->coeff * -1, cursor->expo);
            else 
                printf(" + %lfx^%d", cursor->coeff, cursor->expo);

        }
        cursor = cursor->next;
    }

    if (crlf)
        printf("\n");
}


void attach(node** poly, double coeff, int expo){
    if (islast(poly)){
        // (*poly)->next = *poly;
        node* temp = (node*)malloc(sizeof(node));
        temp->coeff = coeff;
        temp->expo = expo;
        temp->next = *poly;
        (*poly)->next = temp;
        *poly = temp;
        return;
    }

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


void detach(node** poly, int expo){
    node* cursor = *poly;
    node* temp = (node*)malloc(sizeof(node));
    node* follow = (node*)malloc(sizeof(node));

    if ((*poly)->expo == expo){   // 第一個
        temp = cursor;
        while (!islast(&cursor))
            cursor = cursor->next;
        cursor->next = temp->next;
        *poly = temp->next;
        free(temp);
        return;
    }

    while (!islast(&cursor)){
        follow = cursor;
        cursor = cursor->next;
        if (cursor->expo == expo){
            follow->next = cursor->next;
            free(cursor);
            return;
        }
    }
}


double coeff(node** poly, int expo){
    node* cursor = *poly;
    while (!islast(&cursor)){
        if (expo == cursor->expo)
            return cursor->coeff;
        cursor = cursor->next;
    }
    return 0;
}


node** copyPoly(node** source){
    node** target = blankPoly(target);
    while (!islast(source)){
        attach(target, (*source)->coeff, (*source)->expo);
        (*source) = (*source)->next;
    }
    (*source) = (*source)->next;    // 把source從尾指回頭
    return target;
}


void erase(node** poly){
    while((*poly)->coeff != 0 && (*poly)->expo != 0){
        node* temp = *poly;
        free(temp);
        *poly = (*poly)->next;   
    }
    free(*poly);
}


node** padd(node** Poly1, node** Poly2){
    int sum = 0;
    node** resultPoly = blankPoly(resultPoly);
    node* cursor1 = *Poly1;
    node* cursor2 = *Poly2;

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


node** psub(node** Poly1, node** Poly2){
    int sub = 0;
    node** resultPoly = blankPoly(resultPoly);
    node* cursor1 = *Poly1;
    node* cursor2 = *Poly2;

    while (!islast(&cursor1) || !islast(&cursor2)){
        if (cursor1->expo < 0 && islast(&cursor2)){
            attach(resultPoly, cursor1->coeff, cursor1->expo);
            cursor1 = cursor1->next;
            printPoly(resultPoly, 1);
            continue;
        } 
        if (cursor2->expo < 0 && islast(&cursor1)){
            attach(resultPoly, -1 * cursor2->coeff, cursor2->expo);
            cursor2 = cursor2->next;
            continue;
        } 

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


node** pmult(node** Poly1, node** Poly2){
    node* cursor1 = *Poly1;
    node* cursor2 = *Poly2;
    node** resultPoly = blankPoly(resultPoly);

    int mult;
    while (!islast(&cursor1)){
        while (!islast(&cursor2)){
            attach(resultPoly, cursor1->coeff * cursor2->coeff, cursor1->expo + cursor2->expo);
            cursor2 = cursor2->next;
        }
        cursor2 = *Poly2;
        cursor1 = cursor1->next;
    }
    sortPoly(resultPoly);
    return resultPoly;
}


node** pdiv(node** Poly1, node** Poly2){
    node** divident = copyPoly(Poly1);
    node** divisor = copyPoly(Poly2);
    node** Qpoly = blankPoly(Qpoly);
    node** Rpoly = copyPoly(Poly1);

    do{
        node** newterm = blankPoly(newterm);
        attach(newterm, (*divident)->coeff / (*divisor)->coeff, (*divident)->expo - (*divisor)->expo);
        attach(Qpoly, (*newterm)->coeff, (*newterm)->expo);

        divident = psub(divident, pmult(divisor, newterm));
    } while (degree(divident) >= degree(divisor));
    Rpoly = copyPoly(divident);

    printPoly(Qpoly, 0);
    printf(" ... ");
    printPoly(Rpoly, 1);

    erase(Rpoly);
    erase(divisor);
    erase(divident);
    return Qpoly;
}


node** findPoly(int num){
    switch (num){
        case 1:
            return P1;
        case 2:
            return P2;
        case 3:
            return P3;
    }
}


int main(){
    P1 = blankPoly(P1);
    P2 = blankPoly(P2);
    P3 = blankPoly(P3);
    
    printf("Enter 2 Polynomials P1, P2 from the highest term:\n");
    readPoly(P1); 
    readPoly(P2);

    int command = 1;
    while (command){
        printf("-------------------------------------\n");
        printf("0. Quit\n1. show polynomial             2. show coefficient of given power\n3. add term to polynomial      4. delete term of polynomial\n5. P1 + P2                     6. P1 - P2\n7. P1 * P2                     8. P1 / P2\n9. reset polynomial\n");
        printf("-------------------------------------\n");
        printf("P1 = ");printPoly(P1, 1);
        printf("P2 = ");printPoly(P2, 1);
        printf("P3 = ");printPoly(P3, 1);
        printf("-------------------------------------\n> ");
        scanf("%d", &command);
        
        int p;
        int tmp_power;
        double tmp_coeff;
        switch (command){
            case 0:
                continue;

            case 1:

                printf("Which polynomial(1,2,3): "); scanf("%d",&p);
                if (p == 1 || p == 2 || p == 3){
                    printf("P%d = ",p);
                    printPoly(findPoly(p), 1);
                }
                else printf("Polynomial does not exist...\n");
                break;

            case 2:
                printf("Which polynomial(1,2,3): "); scanf("%d",&p);
                printf("Which power: "); scanf("%d", &tmp_power);
                if (p == 1 || p == 2 || p == 3){
                    tmp_coeff = coeff(findPoly(p),tmp_power);
                    if (tmp_coeff - (int)tmp_coeff == 0)
                        printf("x^%d : %.0lf\n",tmp_power, coeff(findPoly(p), tmp_power));
                    else
                        printf("x^%d : %lf\n",tmp_power, coeff(findPoly(p), tmp_power));
                }
                else printf("Polynomial does not exist...\n");
                break;

            case 3:
                printf("Which polynomial(1,2,3): "); scanf("%d",&p);
                printf("Power to add: "); scanf("%d", &tmp_power);
                printf("Coefficient of power: "); scanf("%lf", &tmp_coeff);
                if (p == 1 || p == 2 || p == 3)
                    attach(findPoly(p), tmp_coeff, tmp_power);
                else printf("Polynomial does not exist...\n");
                break;

            case 4:
                printf("Which polynomial(1,2,3): "); scanf("%d",&p);
                printf("Power to delete: "); scanf("%d", &tmp_power);
                if (p == 1 || p == 2 || p == 3)
                    detach(findPoly(p), tmp_power);
                else printf("Polynomial does not exist...\n");
                break;

            case 5: 
                P3 = padd(P1, P2);
                printf("P1 + P2 = P3 = "); printPoly(P3, 1);
                break;
            
            case 6:
                
                P3 = psub(P1, P2);
                printf("P1 - P2 = P3 = "); printPoly(P3, 1);
                break;

            case 7:
                P3 = pmult(P1, P2);
                printf("P1 * P2 = P3 = "); printPoly(P3, 1);
                break;

            case 8:
                printf("P1 / P2 = P3 = ");
                P3 = pdiv(P1, P2);
                break;
            
            case 9:
                printf("Which polynomial(1,2,3): "); scanf("%d",&p);
                if (p == 1 || p == 2 || p == 3)
                    readPoly(findPoly(p));
                else printf("Polynomial does not exist...\n");
                break;
        }
    }
    return 0;	
}