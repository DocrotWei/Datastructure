#include<stdio.h>
#include<stdlib.h>
typedef struct SNode *Stack;
#define ElementType int
#define Maxsize 1000
#define ERROR 0
struct SNode
{
    ElementType Data[Maxsize];
    int Top;
    int StackSize;
};

/*入栈：item 需要入栈的元素 Stack 入栈的堆*/
void Push(ElementType item, Stack PtrS){
   if(PtrS->Top == PtrS->StackSize-1){ //首先应该判断堆栈是否已经满了
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

void IntializeStack(Stack PtrS, int Stacksize){
    PtrS->Top = -1;
    PtrS->StackSize = Stacksize;
}
int main(){
    int M, N, K, i, Temp[Maxsize], Test[Maxsize], index1, index2;
    char flag = 0;
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    scanf("%d %d %d", &M, &N, &K);
    IntializeStack(S, M);
    for(int j = 0; j < K; j++){
        index1 = index2 = 0;
        flag = 0;
        IntializeStack(S, M);
        for(i = 0; i < N; i++){
            scanf("%d", &Test[i]);
            Temp[i] = i + 1;
        }
        while(index1 < N){
            while(S->Top == -1 || S->Data[S->Top] != Test[index1]){
                if(index2 < N && (S->Top != S->StackSize - 1)){
                    Push(Temp[index2++], S);
                }
                else{
                    flag = 1;
                    break;
                }
            }
            if(flag == 1)
                break;
            index1++;
            Pop(S);
        }

        if(flag == 0)
            printf("YES\n");
        else 
            printf("NO\n");
    }
}