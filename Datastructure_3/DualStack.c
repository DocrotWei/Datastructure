#define MaxSize 100
#define ERROR 0
#define ElementType int
typedef struct DSNode *DStack;
struct DSNode{//利用一个数组做双向堆栈
    ElementType Data[MaxSize];
    int Top0;//第一个栈的栈顶
    int Top1;//第二个栈的栈顶
};
/*入栈 输入参数：item入栈元素 Tag选择堆栈:0为第一个堆栈 PtrS堆栈*/
void Push(ElementType item, int Tag, DStack PtrS){
    if(PtrS->Top0 + 1 == PtrS->Top1){//两个栈顶相差1就是相遇了
        printf("堆栈满");
        return;
    }
    else if(Tag == 0){
        PtrS->Data[++(PtrS->Top0)] = item;
        return;
    }
    else{
        PtrS->Data[--(PtrS->Top1)] = item;
        return;
    }
}
/*出栈操作 输入参数：tag堆栈选择：0为第一个 PtrS 堆栈。返回参数：出栈的元素*/
ElementType Pop(int Tag, DStack PtrS){
    if (Tag == 0){//首先判断是那个堆栈
        if(PtrS->Top0 == -1){
            printf("堆栈1满");
            return ERROR;
        }
        else{
            return PtrS->Data[(PtrS->Top0)--];
        }
    }
    else{
       if(PtrS->Top1 == MaxSize){
            printf("堆栈2满");
            return ERROR;
        }
        else{
            return PtrS->Data[(PtrS->Top1)++];
        } 
    }
}