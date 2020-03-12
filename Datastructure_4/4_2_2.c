#include <stdio.h>
#include <string.h>
#define ElemType char
#define Max 10
typedef struct {
    int Left,Right;
    int Level;
} Tree;
Tree T1[Max];

int BuildTree(Tree T[], int n) {
    int Check[n];
    int i,root=-1;
    char l,r;
    for(i = 0; i < n; i++)
        Check[i] = 0;
    if(n) {
        for(i=0; i<n; i++) {
            scanf("\n%c %c", &l, &r);
            {
                if(l!='-') {
                    T[i].Left=l-'0';
                    Check[T[i].Left] = 1;
                } else
                    T[i].Left=-1;
                if(r!='-') {
                    T[i].Right=r-'0';
                    Check[T[i].Right] = 1;
                } else
                    T[i].Right=-1;
            }
        }
    }
    for(i = 0; i < n; i++)
        if(Check[i] == 0){
            root = i;
            break;
        }
    return root;
}

void OutputLeaf(Tree T[], int n, int root){
    int i, flag = 0;
    int front = 0, Rear = 0;
    int Queue[Max];
    memset(Queue, 0, sizeof(Queue));
    for(i = 0; i < n; i++){
        if(T[root].Left != -1)
            Queue[++Rear] = T[root].Left;
        if(T[root].Right != -1)
            Queue[++Rear] = T[root].Right;
        root = Queue[++front];
    }
    for(i = 0; i < n; i++){
        if(T[Queue[i]].Left == -1 && T[Queue[i]].Right == -1)
            if(flag == 0){
                printf("%d", Queue[i]);
                flag = 1;
            }
            else{
                printf(" %d", Queue[i]);
            }
    }
}
int main() {
    int n, root;
    scanf("%d",&n);
    root = BuildTree(T1, n);
    OutputLeaf(T1, n, root);
}