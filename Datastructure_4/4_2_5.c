#include<stdlib.h>
#include <stdio.h>
#include<string.h>
#define MinEle -100000
typedef int ElementType;
#define MAX 1010

typedef struct HeapNode *MinHeap;
struct HeapNode{
    ElementType *Elements;
    int Size;
};

MinHeap HeapCreat(int MaxSize){
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapNode));
    H->Elements = (ElementType *)malloc(sizeof(ElementType) * MAX);
    H->Size = MaxSize;
    return H;
}


void Adjust(MinHeap H, int n, int Parent){
    H->Elements[0] = H->Elements[Parent];
    int  child;
    for(child = 2 * Parent; child <= n; child *= 2){
        if((child < n) && (H->Elements[child] > H->Elements[child + 1]))//if判断是因为没有右孩子了
            child++;
        if(H->Elements[0] <= H->Elements[child])
            break;
        else{
            H->Elements[Parent] = H->Elements[child];
            Parent =child;
        }
    }
    H->Elements[Parent] = H->Elements[0];
}

void BuildMinHeap(MinHeap H, int n){
    int i;
    for(i = n / 2; i > 0; i--)
        Adjust(H, n, i);
}

void InitializeMinHeap(MinHeap H){
    int i;
    for(i = 1; i <= H->Size; i++){
        scanf("%d", &H->Elements[i]);
        BuildMinHeap(H, i);
    }
}

int FindNum(MinHeap H, int temp){
    int i = 0;
    for (i = 1; i <= H->Size; i++)
    {
        if(H->Elements[i] == temp)
            return i;
    }
    return -1;
} 

int main(){
    MinHeap H;
    int N, M, X, Y;
    char test[10], test2[10];
    scanf("%d %d", &N, &M);
    H = HeapCreat(N);
    InitializeMinHeap(H);
    for(int i = 0;i < M; i++){
        scanf("%d %s", &X, &test);
        if(!strcmp(test, "and")){
            scanf("%d %s%s", &Y, &test, &test2);
            if(FindNum(H, X)/2 == FindNum(H, Y)/2)
                printf("T\n");
            else
                printf("F\n");
            continue;
        }
        scanf("%s", &test);
        if(!strcmp(test, "a")){
            scanf("%s%s%d", &test, &test2, &Y);
            if(FindNum(H, Y) == FindNum(H, X)/2)
                printf("T\n");
            else
                printf("F\n");
            continue;
        }
        scanf("%s", &test);
        if(!strcmp(test, "root")){
            X = FindNum(H, X);
            if(X == 1 )
                printf("T\n");
            else
                printf("F\n");
            continue;
        }
        if(!strcmp(test, "parent")){
            scanf("%s%d", &test, &Y);
            if(FindNum(H, Y)/2 == FindNum(H, X))
                printf("T\n");
            else
                printf("F\n");
                continue;
        }
    }
}