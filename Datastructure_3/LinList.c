#include <stdio.h>
#define  ElementType int
#define MaxSize 100 
typedef struct LNode *List;
/*线性结构，注意要有两个参量，一个是最大元素坐标，一个为元素数据 */
struct LNode{
    ElementType Data[MaxSize];
    int Last;
};
/*初始化，主要是针对，抽象数据类型，1。生成空间 2.初始化最大值 3.注意要利用指针，便于操作 */
List MakeEmpty(){
    List Ptrl;
    Ptrl = (List)malloc(sizeof(struct LNode));
    Ptrl->Last = -1;
    return Ptrl;    
}
/*查找操作 1循环查找数据退出后检查结果的合理性 2正常退出，非正常退出*/
int Find(ElementType X, List Ptrl){
    int i = 0;
    while(i <= Ptrl->Last || Ptrl->Data[i]!= X)
        i++;
    if(i > Ptrl->Last)
        return -1; //未查找到返回-1
    else
        return i;//查找到返回坐标
}
/*插入操作，首先注意输入的合法性：1.表是否满了 2.插入位置是否在1 - n+1
其次，移动数组元素从插入位置一个一个往后移*/
void Insert(ElementType X, int i, List Ptrl){
    if (Ptrl -> Last == MaxSize - 1){
        printf("表已经满了");
        return;
    }
    
    if(i < 1 || i > MaxSize + 2){
        printf("位置不合法");
        return;
    }

    for ( int j = Ptrl -> Last; j > i; j--)
        Ptrl ->Data[j + 1] = Ptrl->Data[j];
    Ptrl->Data[i - 1] = X;
    Ptrl ->Last++;   
    return; 
}

void Delete(int i, List Ptrl){
    if(i < 1 || i > MaxSize + 1){
        printf("位置不合法");
    }
    for(int j = i - 1;j < Ptrl->Last; j++)
        Ptrl->Data[j] = Ptrl->Data[j+1];
    Ptrl->Last--;
    return;    
}

