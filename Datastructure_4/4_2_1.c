#include <stdio.h>
#include <string.h>
#define ElemType char
#define Max 10
typedef struct {
    ElemType Data;
    int Left,Right;
} Tree;
Tree T1[Max],T2[Max];

int BuildTree(Tree T[]) {
    int n;
    scanf("%d",&n);
    int check[n];
    memset(check,0,sizeof(check));
    int i,root=-1;
    char l,r;
    if(n) {
        for(i=0; i<n; i++) {
            scanf("\n%c %c %c",&T[i].Data,&l,&r);
            {
                if(l!='-') {
                    T[i].Left=l-'0';
                    check[l-'0']=1;
                } else
                    T[i].Left=-1;
                if(r!='-') {
                    T[i].Right=r-'0';
                    check[r-'0']=1;
                } else
                    T[i].Right=-1;
            }
        }
    }

    for(i=0; i<n; i++) {
        if(!check[i]) {
            root=i;
            break;
        }

    }
    return root;
}
int Isomorphic(int root1,int root2) {
    if(root1==-1&&root2==-1)//空树，同构
        return 1;
    if((root1==-1&&root2!=-1)||(root1!=-1&&root2==-1))//两棵树只有一棵是空树，不同构
        return 0;
    if(T1[root1].Data!=T2[root2].Data)//根结点值不等，不同构
        return 0;
    if(T1[root1].Left==-1&&T2[root2].Left==-1) { //T1 T2的左子树均空，递归判断T1 T2的右子树
        return Isomorphic(T1[root1].Right,T2[root2].Right);
    }
    if(T1[root1].Left!=-1&&T2[root2].Left!=-1) { //T1 T2左子树均不空
        if(T1[T1[root1].Left].Data==T2[T2[root2].Left].Data)//两棵树的左子树的值相等，不用交换左右子树，递归判断
            return Isomorphic(T1[root1].Left,T2[root2].Left)&&Isomorphic(T1[root1].Right,T2[root2].Right);
        else {//两棵树的左子树的值不等，交换左右子树，递归判断
            return Isomorphic(T1[root1].Right,T2[root2].Left)&&Isomorphic(T1[root1].Left,T2[root2].Right);
        }
    }
}

int main() {
    int r1=BuildTree(T1);
    int r2=BuildTree(T2);
    if(Isomorphic(r1,r2))
        printf("Yes");
    else
        printf("No");
    return 0;
}