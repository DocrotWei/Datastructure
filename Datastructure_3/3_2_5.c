#include<stdlib.h>
#include<stdio.h>
typedef struct SNode *Stack;
#define ElementType int
#define Maxsize 100
#define ERROR 0
struct SNode
{
    ElementType Data[Maxsize];
    int Top;
    int StackSize;
};

/*入栈：item 需要入栈的元素 Stack 入栈的堆*/
void Push(ElementType item, Stack PtrS){
   if(PtrS->Top == Maxsize-1){ //首先应该判断堆栈是否已经满了
       printf("ERROR:Full\n");
       return;
   }
   else{ //首先栈顶升高，把元素压入栈中
       PtrS->Data[++(PtrS->Top)] = item;
       return;
   }
}

/*出栈： PtrS堆栈 返回值：出栈的元素*/
ElementType Pop(Stack PtrS){
    if (PtrS->Top == -1){
        printf("堆栈空");
        return ERROR;
    }
    else
        return PtrS->Data[(PtrS->Top)--];//把元素弹出后，在降低栈顶，注意与压栈的区别
}

int IsFull(Stack S){
    return S->Top == S->StackSize -1;
}

int IsEmpty(Stack S){
    return S->Top == -1;
}

void AddQ(ElementType item, Stack S1, Stack S2){
    if(IsFull(S1) && !IsEmpty(S2)){
        printf("ERROR:Full\n");
        return;
    }
    if(!IsFull(S1))
        Push(item, S1);
    else{
        if(IsEmpty(S2)){
            while(!IsEmpty(S1)){
                Push(Pop(S1), S2);
            }
            Push(item, S1);
        }
    }

}

void DeleteQ(Stack S1, Stack S2){
    if(!IsEmpty(S2))
        printf("%d\n", Pop(S2));
    else{
        while(!IsEmpty(S1))
            Push(Pop(S1), S2);
        if(IsEmpty(S2)){
            printf("ERROR:Empty\n");
            return;
        }
        printf("%d\n", Pop(S2));
    }
}

void InitializeQueue(Stack S1, int Size1, Stack S2, int Size2){
    S1->Top = S2->Top = -1;
    S1->StackSize = Size1;
    S2->StackSize = Size2;
}

int main(){
    char Command = 0;
    int Size1, Size2, num;
    Stack S1, S2;
    S1 = (Stack)malloc(sizeof(struct SNode));
    S2 = (Stack)malloc(sizeof(struct SNode));
    scanf("%d %d", &Size1, &Size2);
    if(Size2 < Size1){
        num = Size1;
        Size1 = Size2;
        Size2 = num;
    }
    InitializeQueue(S1, Size1, S2, Size2);
    while(1){
        scanf("%c", &Command);
        switch (Command)
        {
            case 'A':
                scanf("%d", &num);
                AddQ(num, S1, S2);
                break;
            case 'D':
                DeleteQ(S1, S2);
                break;
            case 'T':
                return 0;
        }
    }
}