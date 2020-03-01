#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
#define ElementType int
typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MaxSize];
    int rear;
    int front;
};

/*添加： 输入参数 item添加的元素 PtrQ输入的队列*/
void Add(ElementType item, Queue PtrQ){
    if((PtrQ->rear+1)%MaxSize == PtrQ->front){ //当第一个元素与最后一个元素遇上时队列满
        printf("队列满");
        return;
    }
    else{
        PtrQ->rear = (PtrQ->rear + 1) % MaxSize; //取余操作是为了达到循环的目的
        PtrQ->Data[PtrQ->rear] = item;
    }
}

/*删除 ：输入参数：PtrQ相应的队列 输出参数：从队列弹出的元素*/
ElementType Delete(Queue PtrQ){
    if(PtrQ->rear == PtrQ->front){
        printf("队列已经满了");
        return NULL;
    }
    else{
        PtrQ->front = ((PtrQ->front+1) % MaxSize);
        return PtrQ->Data[PtrQ->front];//因为front是一个空的位置直接把值变了的front元素弹出正好满足要求
    }
}