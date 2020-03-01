#include<stdlib.h>
#include <stdio.h>
#define ElementType int
#define MaxEle 1000

MaxHeap HeapCreat(int MaxSize);
bool IsFull(MaxHeap H);
void Insert(MaxHeap H, ElementType item);
bool IsEmpty(MaxHeap H);
ElementType DeleteMax(MaxHeap H);

typedef struct HeapNode *MaxHeap;
struct HeapNode{
    ElementType *Elements;
    int Size;
    int Capacity;
};

MaxHeap HeapCreat(int MaxSize){
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapNode));
    H->Capacity = MaxSize;
    H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));//数组为最大值加1，是因为树是从1开始
    H->Size = 0;
    H->Elements[0] = MaxEle;//哨兵用来方便后面的程序保证一致性的
    return H;
}

bool IsFull(MaxHeap H){
    return (H->Size == H->Capacity);
}

bool IsEmpty(MaxHeap H){
    return (H->Size == 0);
}

void Insert(MaxHeap H, ElementType item){
    int i;
    if(IsFull(H)){
        printf("Heap is full");
        return;
    }
    i = ++H->Size;//找到新插入的位置
    for(;H->Elements[i/2] < item; i /= 2){//因为之前哨兵的建立所以不用考虑1的影响
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = item;
}

ElementType DeLeteMax(MaxHeap H){
    int Parent, Child;
    ElementType MaxItem, Temp;
    if(IsEmpty(H)){
        printf("Heap is Empty");
        return NULL;
    }

    MaxItem = H->Elements[1];
    Temp = H->Elements[H->Size--];//把队尾元素拿到头
    for(Parent =1; Parent*2 <= H->Size; Parent = Child){
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child +1]))
            Child++;
        if(Temp < H->Elements[Child])
            H->Elements[Parent] = H->Elements[Child];
        else
            break;
    }
    H->Elements[Parent] = Temp;
    return MaxItem;
}       




  