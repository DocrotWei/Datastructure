#define ElementType int
#include<stdlib.h>
#include<stdio.h>

#define MaxSize 100
#define MinEle -1001//哨兵

int H[MaxSize], Size;

void CreatHeap(){
    H[0] = MinEle;
    Size = 0;
}

void Insert(int Item){
    int i;
    if(Size == MaxSize -1)
        return;//堆栈满
    for(i = ++Size; H[i/2] > Item; i /= 2)
        H[i] = H[i/2];
    H[i] = Item;
}

int main(){
    int TreeLongth, Operation;
    int i, j, x;
    scanf("%d %d", &TreeLongth, &Operation);
    CreatHeap();
    for(i =0; i < TreeLongth; i++){
        scanf("%d", &x);
        Insert(x);
    }
    for(i = 0; i < Operation; i++){
        scanf("%d", &j);
        for(; j > 0; j /= 2)
            printf("%d", H[j]);
        printf("\n");
    }
    return 0;
}