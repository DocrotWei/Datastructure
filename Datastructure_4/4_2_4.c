#include <stdio.h>
#include <malloc.h>
#define max 1000
typedef struct TNode {
    int Data;
    struct TNode *Left;
    struct TNode *Right;
}*BiTree;
BiTree BuildTree(BiTree T,int X) {//建立二叉搜索树
    if(!T) {
        T=(BiTree)malloc(sizeof(BiTree));
        T->Data=X;
        T->Left=T->Right=NULL;
    } else {
        if(X<T->Data)
            T->Left=BuildTree(T->Left,X);
        else
            T->Right=BuildTree(T->Right,X);
    }
    return T;
}
int tree[max];
int k1=0;
void PreOrderTraverse(BiTree T) {//前序遍历
    if(T) {
//        printf("%d ",T->Data);
        tree[k1++]=T->Data;
        PreOrderTraverse(T->Left);
        PreOrderTraverse(T->Right);


    }
}
int k2=0;
void MirrorPreOrder(BiTree T) {//镜像前序遍历
    if(T) {
//        printf("%d ",T->Data);
        tree[k2++]=T->Data;
        MirrorPreOrder(T->Right);
        MirrorPreOrder(T->Left);

    }
}
int flag=0;
void PostOrder(BiTree T) {//后序遍历
    if(T) {
        PostOrder(T->Left);
        PostOrder(T->Right);
        if(flag)
            printf(" ");
        else flag=1;
        printf("%d",T->Data);
    }
}
int tag=0;
void MirrorPostOrder(BiTree T) {//镜像后序遍历
    if(T) {
        MirrorPostOrder(T->Right);
        MirrorPostOrder(T->Left);
        if(tag)
            printf(" ");
        else tag=1;
        printf("%d",T->Data);
    }
}
int IsSame(int a[],int tree[],int n) {//判断输入数据是否与前序遍历顺序一致
    int i;
    for(i=0; i<n; i++) {
        if(a[i]!=tree[i])
            return 0;
    }
    return 1;
}
int main() {
    int i,x,n;
    scanf("%d",&n);
    int a[n];
    BiTree T=NULL;
    for(i=0; i<n; i++) {
        scanf("%d",&a[i]);
        T=BuildTree(T,a[i]);
    }
    PreOrderTraverse(T);
    if(IsSame(a,tree,n)) {
        printf("YES\n");
        PostOrder(T);
    } else {
        MirrorPreOrder(T);
        if(IsSame(a,tree,n)) {
            printf("YES\n");
            MirrorPostOrder(T);
        } else
            printf("NO");
    }
    return 0;

}