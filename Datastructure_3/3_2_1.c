#include<stdlib.h>
#include<stdio.h>
typedef struct PNode *PtrToPNode;
struct PNode{
    int Coef;
    int Expon;
    PtrToPNode Next;
};

typedef PtrToPNode Polynomial;

void Attach(int C, int E, Polynomial *pRear){
    Polynomial temp;
    temp = (Polynomial)malloc(sizeof(struct PNode));
    temp->Coef = C;
    temp->Expon = E;
    temp->Next = NULL;
    (*pRear)->Next = temp;
    *pRear = temp;
}

Polynomial InputPolynomial(){
    Polynomial P, Rear, t;
    int c, e, flag = 0;
    P = (Polynomial)malloc(sizeof(struct PNode));
    Rear = P;
    while(scanf("%d %d", &c, &e) != EOF){
        if(flag == 0 && e == 0){
            P = NULL;
            return P;
        }
        else{
            flag = 1;
            Attach(c, e, &Rear);
        }
    }
    t = P;
    P = P->Next;
    free(t);
    return P;

}

Polynomial Differentiation(Polynomial P){
    Polynomial P1, P2;
    P1 = P;
    while(P1 && P1->Expon){
        P1->Coef = P1->Coef * P1->Expon;
        P1->Expon = P1->Expon - 1;
        P2 = P1;
        P1 = P1->Next;
    }
    if(P1){
        P2->Next = NULL;
        free(P1);
    }
    return P;
}

void PrintPolynomial(Polynomial P){
    int flag = 0;
    while(P){
        if(!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d %d", P->Coef, P->Expon);
        P = P->Next;
    }
    printf("\n");
}
int main(){
    Polynomial P;

    P = InputPolynomial();
    if(P == NULL){
        printf("0 0");
    }
    else{
        P = Differentiation(P);
        PrintPolynomial(P);
    }
    return 0;
}