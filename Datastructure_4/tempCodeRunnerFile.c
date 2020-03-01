#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode{
    int v;
    Tree left, right;
    int flag;       //某节点被访问过则设为1；否则设为0
};

Tree MakeTree(int N);
Tree NewNode(int V);
Tree Insert(Tree T, int V);
int check(Tree T, int V);
int Judge(Tree T, int  N);
void ResetT(Tree T);        //清除T中各节点的lag标记
void FreeTree(Tree T);      //释放T的空间

int main()
{
    int N, L, i;
    Tree T;

    scanf("%d", &N);        //how many tree node
    while(N){
        scanf("%d",&L);     //how many comparison sequence
        T = MakeTree(N);    //use numnbr N to make a new tree
        for(i=0; i<L; i++){
            if(Judge(T,N))
                printf("yes\n");
            else
                printf("no\n");
            ResetT(T);      //clear T flag
        }
        FreeTree(T);
        scanf("%d",&N);
    }
    return 0;
}

Tree MakeTree(int N)
{

    Tree T;
    int i, V;

    scanf("%d",&V);
    T = NewNode(V);
    for(i=1; i<N; i++){
        scanf("%d",&V);
        T=Insert(T,V);
    }
    return T;
}

Tree NewNode(int V)
{
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->v = V;
    T->left = T->right = NULL;
    T->flag =0;
    return T;
}

Tree Insert(Tree T, int V)
{
    if(!T)
        T = NewNode(V);
    else{
        if(V>T->v)
            T->right = Insert(T->right, V);
        else
            T->left = Insert(T->left,V);
    }
    return T;
}

int check(Tree T, int V)
{

    if(T->flag){
        if(V<T->v)
            return check(T->left, V);
        else if (V>T->v)
            return check(T->right, V);
        else return 0;
    }
    else{
        if(V==T->v){
            T->flag =1;
            return 1;
        }
        else return 0;
    }
}

int Judge(Tree T, int  N)
{
    int i, V, fflag=0;      //fflag:0代表目前还一致，1代表已经不一致

    scanf("%d",&V);
    if(V != T->v)
        fflag = 1;
    else
        T->flag = 1;

    for(i = 1; i<N; i++){
        scanf("%d",&V);
        if((!fflag)&&(!check(T,V)))
            fflag = 1;
    }
    if(fflag)   return 0;
    else    return 1;
}

void ResetT(Tree T)
{
    if(T->left) ResetT(T->left);
    if(T->right)    ResetT(T->right);
    T->flag = 0;
}

void FreeTree(Tree T)
{
    if(T->left) FreeTree(T->left);
    if(T->right)    FreeTree(T->right);
    free(T);
}
