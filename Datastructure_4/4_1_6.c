#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXS 30

typedef char TreeType[MAXS + 1];
typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode
{
    TreeType Tree;
    BinTree Right;
    BinTree Left;
    int Cnt;
};


BinTree Insert(TreeType InsertEle, BinTree BST){
    if(!BST){//找到空结点进行插入
        BST = (BinTree)malloc(sizeof(struct TreeNode));
        strcpy(BST->Tree, InsertEle);
        BST->Left = BST->Right = NULL;
        BST->Cnt = 1;
    }
    else{
        if(strcmp(InsertEle ,BST->Tree) > 0)
            BST->Right = Insert(InsertEle, BST->Right);
        else if(strcmp(InsertEle ,BST->Tree) < 0)
            BST->Left = Insert(InsertEle, BST->Left);
        else
            BST->Cnt++;
    }
    return BST;
}

void Output(int N, BinTree T){
    if(!T)
        return;
    Output(N, T->Left);
    printf("%s %.4lf%c\n", T->Tree, (double)T->Cnt/(double)N * 100.0, '%');
    Output(N, T->Right);
}

int main(){
    int N,i;
    TreeType Name;
    BinTree T = NULL;
    scanf("%d\n", &N);
    for(int i = 0; i < N; i++){
        gets(Name);
        T = Insert(Name, T);
    }
    Output(N, T);
    return 0;
}