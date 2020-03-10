#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1000
#define ERROR -1
typedef int ElementType;
struct QNODE
{
    ElementType Customer[MAXSIZE];
    int Rear;
    int Front;
};

typedef struct QNODE *PtrToQnode;
typedef PtrToQnode Queue;

void InitializeQueue(Queue Q){
    Q->Front = Q->Rear = 0;
}

int IsEmptyQ(Queue Q){
    return Q->Front == Q->Rear;
}

void AddQ(Queue Q, ElementType item){
    if((Q->Rear + 1) % MAXSIZE == Q->Front){
        printf("堆栈满");
        return;
    }
    Q->Customer[++Q->Rear % MAXSIZE] = item;
}

int DeleteQ(Queue Q){
    if(Q->Front == Q->Rear){
        printf("队列空");
        return ERROR;
    }
    else
        return Q->Customer[(++Q->Front) % MAXSIZE];
}

int main(){
    Queue A, B;
    int N, item, flag = 0;
    A = (Queue)malloc(sizeof(struct QNODE));
    B = (Queue)malloc(sizeof(struct QNODE));
    InitializeQueue(A);
    InitializeQueue(B);
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &item);
        if(item % 2 == 1)
            AddQ(A, item);
        else if(item % 2 == 0)
            AddQ(B, item);
    }

    while(!IsEmptyQ(A) && !IsEmptyQ(B)){
        if(flag == 0){
            printf("%d", DeleteQ(A));
            flag = 1;
        }
        else
            printf(" %d", DeleteQ(A));
        if(!IsEmptyQ(A))
            printf(" %d", DeleteQ(A));
        printf(" %d", DeleteQ(B));
    }
    while(!IsEmptyQ(A)){
        if(flag == 0){
            printf("%d", DeleteQ(A));
            flag = 1;
        }
        else
            printf(" %d", DeleteQ(A));
    }

    while(!IsEmptyQ(B)){
        if(flag == 0){
            printf("%d", DeleteQ(B));
            flag = 1;
        }
        else
            printf(" %d", DeleteQ(B));
    }
    printf("\n");
    return 0;
}