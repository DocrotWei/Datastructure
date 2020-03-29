#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct LNode *Link;
struct LNode{
    Link Next;
    int Item;
};

Link NewNode(Link L,int item){
    if(L == NULL){
        L = (Link)malloc(sizeof(struct LNode));
        L->Item = item;
        L->Next = NULL;
        return L;
    }
    else{
        Link newNode;
        newNode = (Link)malloc(sizeof(struct LNode));
        newNode->Item = item;
        newNode->Next = NULL;
        L->Next = newNode;
        L = L->Next;
        return L;
    }
}

int main(){
    Link Head1 = NULL, Head2 = NULL, Temp, output = NULL;
    Head1 = NewNode(Head1, 0);
    Head2 = NewNode(Head2, 0);
    int i, item, flag = 0;
    for(i = 0; i < 2; i++){
        Temp = i % 2?Head2:Head1;
        while(1){
        scanf("%d", &item);
        if(item == -1)
            break;
        Temp = NewNode(Temp, item);
        }
    }
    Temp = Head1;
    Head1 = Head1->Next;
    free(Temp);
    Temp = Head2;
    Head2 = Head2->Next;
    free(Temp);
    output = Temp = NewNode(output, 0);
    while(Head2 != NULL && Head1 != NULL){
        if(Head1->Item < Head2->Item)
            Head1 = Head1->Next;
        else if(Head2->Item < Head1->Item)
            Head2 = Head2->Next;
        else{
            Temp = NewNode(Temp, Head2->Item);
            Head1 = Head1->Next;
            Head2 = Head2->Next;
        }
    }
    Temp = output;
    output = output->Next;
    free(Temp);
    if(output == NULL)
        printf("NULL");
    else{
        while(output != NULL){
            if(flag == 1)
                printf(" ");
            else
                flag = 1;
            printf("%d", output->Item);
            output = output->Next;
        }
    }
}