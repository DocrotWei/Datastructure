#include<Stdlib.h>
typedef struct PolyNode *Polynomial;
struct PolyNode{
    int coef;
    int expon;
    Polynomial Next;
};
Polynomial P1, P2;

/*函数明：Attch
    功能：把新增的项接到多项式的末尾
    输入参数： Coef 多项式阶数 Expon 多项系数 *Rear 队尾指针
    */
void Attch(int Coef, int Expon, Polynomial *PtrRear){//因为c语言值传递的原因想改变PtrRear的最终指向所以采用了双重指针
    Polynomial NewCell;
    NewCell->coef = Coef;
    NewCell->expon = Expon;
    NewCell->Next = NULL;
    (*PtrRear)->Next = NewCell;//把新的元素加到队尾
    *PtrRear = NewCell;//改变队尾指针的值
}

int CompareExpon(int P1Expon, int P2Expon){
    if(P1Expon > P2Expon)
        return 1;//第一项的指数大于第二项
    else if(P1Expon < P2Expon)
        return -1;
    else
        return 0;
}   

Polynomial PolyAdd(Polynomial P1, Polynomial P2){
    Polynomial front, rear, temp;//temp是为了释放头结点的空间设置的
    int Test;//用来检测当两个指数相等的时候是否需要保留该值
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    front = rear;
    while(P1 && P2){
        switch(CompareExpon(P1->expon, P2->expon)){
            case 1:
                Attch(P1->coef, P1->expon, &rear);
                P1 = P1->Next;
                break;
            case -1:
                Attch(P2->coef, P2->expon, &rear);
                P2 = P2->Next;
                break;
            case 0:
                Test = P1->coef + P2->coef;
                if(Test)
                    Attch(Test, P1->expon, &rear);
                P1 = P1->Next;
                P2 = P2->Next;
        }
    }
    for(;P1;P1 = P1->Next)
        Attch(P1->coef, P1->expon, &rear);
    for(;P2;P2 = P2->Next)
        Attch(P2->coef, P2->expon, &rear);
    rear->Next = NULL;
    temp = front;
    front = front->Next;
    free(temp);
    return front;
}