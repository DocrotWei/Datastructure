#include <stdio.h>
#define ElementType int
#define NULL 0
#define ERROR -1;

typedef struct LNode * List;
struct  LNode
{
    ElementType Data;/* data */
    List Next;
};

struct LNode L;
List PtrL;
/*因为链表的特殊性，不能直接得到角标元素，所以只能采用遍历的方法得到表的长度*/
int Length(List PtrL){
    List p = PtrL;
    int i = 0;
    while(p){
        p = p ->Next;
        i++;
    }

    return i;
}
/*查找第几个元素要点，退出条件，1找到2没找到
返回：1返回查找元素 ，2。返回无*/
List FindKth(int K, List PtrL){
    int i = 0;
    List p = PtrL;
    while(p != NULL && i < K){
        p = p->Next;
        i++;
    }
    if(i == K)
        return p;
    else
        return NULL;
}
/*查找指定元素，需要注意退出条件*/
List Find(ElementType F, List PtrL){
    List L = PtrL;
    while(L != NULL && L->Data != F)
        L = L-> Next;
    if(L != NULL)
        return L;
    else
        return NULL;
}
/*插入操作1.找到要插入位置的前面一个元素2.申请新的空间3。进行插入操作
    注意，如果是头结点需要返回新的头指针*/

List Insert(ElementType I, int i, List PtrL){
    List s,p;//为插入新的元素创建的新的空间
    if (i == 1){
        s = (List)malloc(sizeof(struct LNode));
        s->Data = I;
        s->Next = PtrL;
        return s;//返回此时的头指针s
    }
    p = FindKth(i-1, PtrL);
    if(p == NULL){
        printf("参数错误");
        return NULL;
    }
    else{
        s->Next = p->Next;
        p->Next = s;
        return PtrL;
    }

}
/*删除第i个结点位置的元素,i为第i个位置*/
List Delete(int i, List PtrL){
    List s,p;
    if(i == 1){//首先要注意头节点删除的问题，其次要注意头节点是否为空的问题
        if(PtrL == NULL)
            return NULL;
        s = PtrL;
        PtrL = PtrL->Next;
        free(s);
        return PtrL;
    }
    p = FindKth(i-1, PtrL);//此处要注意首先i-1要存在，其次i要存在
    if(p == NULL){//i-1要存在
        printf("第%d个结点不存在",i-1);
        return NULL;
    }
    else if(p->Next == NULL){//确认第i个元素存在
        printf("第%d个结点不存在",i);
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}