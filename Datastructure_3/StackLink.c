#define ElementType int
#include <stdlib.h>
typedef struct SNode *Stack;
struct SNode{
    ElementType Data;
    Stack Next; 
};
/*创建一个新的堆栈，即创建一个新的结点*/
Stack CreateStack(){
    Stack S;
    S = (Stack)melloc(sizeof(struct SNode));//建立一个头指针，指向第一个元素
    S->Next = NULL;
    return S;
}
/*判断是否为空 输入元素：堆栈名 输出参数：1为空*/
int IsEmpty(Stack S){
    if(S->Next == NULL){
        return 1;
    }
    else 
        return 0;
}
/*压栈操作 item要压栈的元素 Ptrs堆栈的头指针*/
void Push(ElementType item, Stack PtrS){//有点类似于链式线性表的插入操作
    Stack TmpCell;
    TmpCell = (Stack)melloc(sizeof(struct SNode));
    TmpCell->Data = item;
    TmpCell->Next = PtrS->Next;
    PtrS->Next = TmpCell;
}

/*出栈 输入参数：S栈顶指针 输出参数：栈顶的元素*/
ElementType Pop(Stack PtrS){
    Stack PopCell;
    ElementType TopEle;
    if(IsEmpty(PtrS)){
        printf("堆栈空");
        return NULL;
    }
    else{
        PopCell = PtrS->Next;
        PtrS->Next = PopCell->Next;
        TopEle = PopCell->Data;
        free(PopCell);
        return TopEle;
    }
}
/*注意理解的时候应该结合图像，注意各部分的值*/
  
