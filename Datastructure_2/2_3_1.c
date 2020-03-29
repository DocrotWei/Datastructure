#include<stdio.h>
#include<string.h>
#define MAXSIZE 100
int GetMin(int A[], int B[],int N){
    int min = 101, i, minI;
    for(i = 0; i < N; i++){
        if(A[i] < min && B[i] != 1){
            min = A[i];
            minI = i;
            }
    }
    return minI;
}

int main(){
    int N, D, Now, Count, Pirate[MAXSIZE], Visited[MAXSIZE], i, j, minI, Dnum;
    scanf("%d %d", &D, &N);
    memset(Pirate, 0, sizeof(int) * N);
    memset(Visited, 0, sizeof(int) * N);
    Now = N-2;//现在分配的起始坐标
    Dnum = D;
    for(i = 0; i < N-2; i++){//总共分配的次数
        Count = (N-Now) % 2? (N- Now)/ 2 + 1:(N- Now)/ 2 ;//需要非配砖石的人数
        for(j = 0; j < Count; j++){
            minI = GetMin(Pirate + Now , Visited + Now , N - Now) + Now;
            Pirate[minI]++;
            Visited[minI] = 1;
            Dnum -= Pirate[minI];
        }
        for(j = Now; j < N; j++){
            if(Visited[j] != 1){
                Pirate[j] = 0;
            }
            else{
                Visited[j] = 0;
            }
        }
        Pirate[Now-1] = Dnum;
        Now--;
        Dnum = D;
    }
 printf("%d", Pirate[0]);
}