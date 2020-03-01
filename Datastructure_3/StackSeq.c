typedef struct SNode *Stack;
#define ElementType int
#define Maxsize 10
#define ERROR 0
struct SNode
{
    ElementType Data[Maxsize];
    int Top;
};

/*入栈：item 需要入栈的元素 Stack 入栈的堆*/
void Push(ElementType item, Stack PtrS){
   if(PtrS->Top == Maxsize-1){ //首先应该判断堆栈是否已经满了
       printf("堆栈满");
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
