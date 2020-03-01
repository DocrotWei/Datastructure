#include<stdio.h>
#include<stdlib.h>
#define ElementType int
#define ERROR 0
struct Node{//单元结点用来存放普通正常元素的
    ElementType Data;
    struct Node *Next;
};
//注意单向链表的头作为队列的头，链尾作为队列的尾
typedef struct QNode *Queue;
struct QNode{//头结点指向的结点，记录队尾和队头
    struct Node *rear;
    struct Node *front;
};
Queue PtrQ;

/*出队操作： 
    输入元素：PtrQ队列地址  
    输出元素：出队的元素*/
ElementType DeleteQ(Queue PtrQ){
    struct Node *FrontCell;
    ElementType FrontEle;
    if(PtrQ->rear == NULL){
        printf("队列空");
        return ERROR;
    }
    FrontCell = PtrQ->front;
    if(PtrQ->front = PtrQ->rear)
        PtrQ->front = PtrQ->rear = NULL;
    else
        PtrQ->front = PtrQ->front->Next;
    FrontEle = FrontCell->Data;
    free(FrontCell);
    return FrontEle;
}

/*入队操作：
    输入元素：item入队元素 PtrQ队列*/
void AddQ(ElementType item, Queue PtrQ){
    struct Node *RearCell;
    RearCell = (struct Node*)melloc(sizeof(struct Node*));
    RearCell->Data = item;
    if(PtrQ->front == NULL)
        PtrQ->front = PtrQ->rear = RearCell;
    else{
        PtrQ->rear->Next = RearCell;
        PtrQ->rear = RearCell;
    }
}