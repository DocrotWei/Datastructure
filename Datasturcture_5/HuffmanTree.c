#include<stdlib.h>
#include <stdio.h>
#define ElementType HUffmanTree
#define MinEle -10001

typedef struct TreeNode *HUffmanTree;
struct TreeNode{
    int Weight;//用来计算树的权重
    HUffmanTree Left, Right;
};

typedef struct HeapNode *MinHeap;
struct HeapNode{
    ElementType *Elements;
    int Size;
    int Capacity;
};

MinHeap HeapCreat(int MaxSize);
bool IsFull(MinHeap H);
void Insert(MinHeap H, ElementType item);
bool IsEmpty(MinHeap H);
ElementType DeleteMin(MinHeap H);
MinHeap BUildMinHeap(MinHeap H);
HUffmanTree BuildHuffmanTree(MinHeap H);


MinHeap BuildMinHeap(MinHeap H){
    int Parent, Child, i;
    ElementType Temp;
    for(i = H->Size/2; i>0; i--){
        Temp = H->Elements[i];
        for(Parent = i; Parent*2 <= H->Size; Parent = Child){
            Child = 2 * Parent;
            if((Child != H->Size) && (H->Elements[Child]->Weight > H->Elements[Child+1]->Weight))
                Child++;
            if(Temp->Weight > H->Elements[Child]->Weight)
                H->Elements[Child] = H->Elements[Parent];
            else 
                break;
        } 
        H->Elements[Parent] = Temp;
    }
}
MinHeap HeapCreat(int MaxSize){
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapNode));
    H->Capacity = MaxSize;
    H->Size = 0;
    for(int i = 0; i < MaxSize; i++){
        H->Elements[i]->Left = H->Elements[i]->Right = NULL;
        H->Elements[i]->Weight = 0;
    }
    H->Elements[0]->Weight = MinEle;//哨兵用来方便后面的程序保证一致性的
    return H;
}

bool IsFull(MinHeap H){
    return (H->Size == H->Capacity);
}

bool IsEmpty(MinHeap H){
    return (H->Size == 0);
}

void Insert(MinHeap H, ElementType item){
    int i;
    if(IsFull(H)){
        printf("Heap is full");
        return;
    }
    i = ++H->Size;//找到新插入的位置
    for(;H->Elements[i/2]->Weight > item->Weight; i /= 2){//因为之前哨兵的建立所以不用考虑1的影响
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = item;
}

ElementType DeLeteMin(MinHeap H){
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
        if ((Child != H->Size) && (H->Elements[Child] > H->Elements[Child +1]))
            Child++;
        if(Temp < H->Elements[Child])
            H->Elements[Parent] = H->Elements[Child];
        else
            break;
    }
    H->Elements[Parent] = Temp;
    return MaxItem;
}

HUffmanTree Huffman(MinHeap H){
    int i;
    HUffmanTree T;
    BuildMinHeap(H);
    for(i = 1; i < H->Size; i++){
        T = malloc(sizeof(struct TreeNode));
        T->Left = DeLeteMin(H);
        T->Right = DeLeteMin(H);
        T->Weight = T->Left->Weight + T->Right->Weight;
        Insert(H, T);
    }
    T = DeLeteMin(H);
    return T;
}