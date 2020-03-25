#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<stdbool.h>
#define MaxCapleSize 100001
#define MaxPeopleSize 10000
#define NameNum 5
typedef char NameType[NameNum + 1];
typedef struct{
    NameType CopleName;
    NameType Name;
    int Visited;
}CapleArray[MaxCapleSize];
bool Compare( int a, int b){
    return a < b;
}
using namespace std;

int main(){
    int  N, i, C1, C2, *Rank, cnt = 0;
    NameType Name, Name1;
    CapleArray Caple;
    memset(Caple, '\0', MaxCapleSize);
    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%s %s\n", &Name, &Name1);
        C1 = atoi(Name);
        C2 = atoi(Name1);
        strcpy(Caple[C1].CopleName, Name1);
        strcpy(Caple[C2].CopleName, Name);
    }
    scanf("%d", &N);
    Rank = (int *)malloc(sizeof(int) * N);
    for(i = 0; i < N; i++){
        scanf("%s" ,&Name);
        Rank[i] = atoi(Name);
        strcpy(Caple[Rank[i]].Name, Name);
        Caple[Rank[i]].Visited = 1;
    }
    sort(Rank, Rank+N, Compare);
    for(i = 0; i < N; i++){
        if(Caple[Rank[i]].CopleName[0] == '\0')
            cnt++;
        else{
            if(Caple[atoi(Caple[Rank[i]].CopleName)].Visited == 1)
                Rank[i] = -1;
            else
                cnt++;
        }
    }
    printf("%d\n", cnt);
    cnt = 0;
    for(i = 0; i < N; i++){

        if(cnt != 0 && Rank[i] != -1)
            printf(" %s", Caple[Rank[i]].Name);
        else if(Rank[i] != -1){
            printf("%s", Caple[Rank[i]].Name);
            cnt = 1;
            }
    }
}