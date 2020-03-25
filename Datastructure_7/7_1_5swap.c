#include<stdio.h>
#include<stdlib.h>
typedef int ElemenType;
struct SNode{
    ElemenType item;
    int Wrong;
};
typedef struct SNode* PtrToSNode;
typedef PtrToSNode SortType;

void Swap(SortType S, int i, int j){
    int temp;
    temp = S[i].item;
    S[i].item = S[j].item;
    S[j].item = temp;
}

int main(){
    int N, i, num = 0, Pre, Next;
    scanf("%d", &N);
    SortType S;
    S = (SortType)malloc(sizeof(struct SNode) * N);
    for(i = 0; i < N; i++){
        scanf("%d", &S[i].item);
        if(S[i].item != i){
            S[i].Wrong = 1;
        }
    }

    for(i = 0; i < N; i++){
        if(S[i].Wrong == 1){
            if(S[0].Wrong == 0){
                Swap(S, 0, i);
                S[0].Wrong = 1;
                num++;
            }

            while(S[0].Wrong != 0){
                Next = S[0].item;
                Swap(S, 0, Next);
                num++;
                S[Next].Wrong = 0;
                if(S[0].item == 0){
                    S[0].Wrong = 0;
                }
            }
        }
    }
    printf("%d", num);
}

