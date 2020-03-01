typedef int ElementType;
typedef int SetName;
#define MaxSize 10
typedef ElementType SetType[MaxSize];
#include<stdio.h>

SetName Find(SetType S, ElementType X){
    if(S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]);
}

void Union(SetType S, SetName Root1, SetName Root2){
    if(S[Root1] < S[Root2]){//实际上是1大
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }

    else
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

void Initial(SetType S, int N){
    int i;
    for(i = 0; i < N; i++)
        S[i] = -1;
}

void InputConnection(SetType S){
    int Ele1, Ele2;
    SetName Root1, Root2;
    scanf("%d %d", &Ele1, &Ele2);
    Root1 = Find(S, Ele1-1);
    Root2 = Find(S, Ele2-1);
    if(Root1 == Root2)
        return;
    else
        Union(S, Root1, Root2);
} 

void CheckConnection(SetType S){
        int Ele1, Ele2;
    SetName Root1, Root2;
    scanf("%d %d", &Ele1, &Ele2);
    Root1 = Find(S, Ele1-1);
    Root2 = Find(S, Ele2-1);
    if(Root1 == Root2){
        printf("yes\n");
        return;
    }
    else
    {
        printf("no\n");
        return;
    }
}

void StopConnection(SetType S, int n){
    int i,flag = 0;
    for(i = 0; i < n; i++)
        if(S[i] < 0)
            flag++;
    if(flag > 1)
        printf("There are %d components", flag);
    else
        printf("The network is connected");
}

int main(){
    SetType S;
    int ComputerNum;
    char In;
    scanf("%d",&ComputerNum);
    Initial(S, ComputerNum);
    do
    {
        scanf("%c", &In);
        switch (In)
        {
        case 'C': 
            CheckConnection(S);
            break;
        case 'I':
            InputConnection(S);
            break;
        case 'S':
            StopConnection(S, ComputerNum);
            break;
        default:
            break;
        }
    } while (In != 's');
    
    return 0;
}