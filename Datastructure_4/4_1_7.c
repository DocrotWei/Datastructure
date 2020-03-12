#include<stdio.h>
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

void LinkComputer(SetType S, int C1, int C2){
    int Root1, Root2;
    Root1 = Find(S, C1);
    Root2 = Find(S, C2);
    if(Root1 != Root2)
        Union(S, C1, C2);
    return;
}

void CheckComputer(SetType S, int C1, int C2){
    int Root1, Root2;
    Root1 = Find(S, C1);
    Root2 = Find(S, C2);
    if(Root1 != Root2)
        printf("no\n");
    else
        printf("yes\n");
    return;
}

void StopLink(SetType S, int N){
    int Cnt = 0;
    for(int i = 0; i < N; i++){
        if(S[i] < 0)
            Cnt++;
    }
    if(Cnt == 1)
        printf("The network is connected.");
    else 
        printf("There are %d components.", Cnt);
}

int main(){
    int N;
    ElementType C1, C2;
    char CMD;
    SetType S;
    scanf("%d", &N);
    InitializeSet(S, N);
    do
    {
        scanf("%c", &CMD);
        switch (CMD)
        {
        case 'I':
            scanf("%d %d", &C1, &C2);
            LinkComputer(S, C1, C2);
            break;
        case 'C':
            scanf("%d %d", &C1, &C2);
            CheckComputer(S, C1, C2);
            break;
        case 'S':
            StopLink(S, N);
            break;
        }
    } while (CMD != 'S');
    return 0;
}