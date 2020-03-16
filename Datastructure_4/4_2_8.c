#include<stdio.h>
#include<string.h>
#define MaxSize 10100
typedef int ElementType;
typedef ElementType SetType[MaxSize]; 

int Find(SetType S, ElementType Item){
    int i;
    if(S[Item] < 0)
        return Item;
    return S[Item] = Find(S, S[Item]);
}

void Union(SetType S, ElementType Ele1, ElementType Ele2){
    int Root1, Root2;
    Root1 = Find(S, Ele1);
    Root2 = Find(S, Ele2);
    if(S[Root1] <= S[Root2]){
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
    else{
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

void InitializeSet(SetType S, int N){
    while(N+1){
        S[--N] = -1;
    }
}

void LinkPeople(SetType S, int C1, int C2){
    int Root1, Root2;
    Root1 = Find(S, C1);
    Root2 = Find(S, C2);
    if(Root1 != Root2)
        Union(S, C1, C2);
    return;
}

void CheckPeople(SetType S, int C1, int C2){
    int Root1, Root2;
    Root1 = Find(S, C1);
    Root2 = Find(S, C2);
    if(Root1 != Root2)
        printf("N\n");
    else
        printf("Y\n");
    return;
}

void OutputLink(SetType S, int N, int *Check){
    int Cnt = 0;
    int Num = 0;
    for(int i = 0; i < N; i++){
        if(Check[i] == 1)
            Num++;
    }
    for(int i = 1; i <= Num; i++){
        if(S[i] < 0)
            Cnt++;
    }
    printf("%d %d\n", Num, Cnt);
}

int main(){
    int N, K, i, j, P[MaxSize], Check[MaxSize];
    ElementType C1, C2;
    SetType S;
    memset(Check, 0, sizeof(int) * MaxSize);
    InitializeSet(S, MaxSize);
    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%d", &K);
        for(j = 0; j < K; j++){
            scanf("%d", &P[j]);
            if(Check[P[j]] == 0)
                Check[P[j]] = 1;
            if(j > 0)
                LinkPeople(S, P[j], P[j-1]);
        }
    }
    scanf("%d", &N);
    OutputLink(S, MaxSize, Check);
    for(i = 0; i < N; i++){
        scanf("%d %d", &P[0], &P[1]);
        CheckPeople(S, P[0], P[1]);
    }
    return 0;
}