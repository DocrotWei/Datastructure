#include<stdio.h>
#include<string.h>
#define MAXSIZE 1000
typedef int SizeType;
typedef struct{
    int CaseNum;
    SizeType Size;
} Item[MAXSIZE];

typedef struct{
    int CaseSize;
    int Visited;
} Case[MAXSIZE];
int main(){
    int N, M, CaseSum = 0;
    Item item;
    Case C;
    scanf("%d", &N);
    M = N;
    for(int i = 0; i < M; i++){
        C[i].CaseSize = 100;
        C[i].Visited = 0;
        item[i].CaseNum = 0;
        item[i].Size = 0;
    }
    for (int i = 0; i < M; i++){
        scanf("%d", &(item[i].Size));
        for(int j = 0; j < MAXSIZE; j++){
            if(C[j].CaseSize >= item[i].Size){
                item[i].CaseNum = j + 1;
                C[j].CaseSize -= item[i].Size;
                if(C[j].Visited == 0){
                    C[j].Visited = 1;
                    CaseSum++;
                }
                break;
            }
        }
    }
    for(int i = 0; i < M; i++){
        printf("%d %d\n", item[i].Size, item[i].CaseNum);
    }
    printf("%d\n", CaseSum);
    return 0;   
}