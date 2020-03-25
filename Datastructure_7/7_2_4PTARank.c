#include<stdbool.h>
#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#define IDSIZE 18
typedef char IDType[IDSIZE + 1];
typedef struct SNode{
    int FinalRank;
    int ExamRank;
    int ExamNum;
    int Point;
    IDType IDNum;
}Student[40000];

bool Compare(struct SNode a,  struct SNode b){
    if(a.Point == b.Point)
        return strcmp(a.IDNum, b.IDNum) < 0;
    return a.Point > b.Point;
}

using namespace std;


int main(){
    int N, K, i, j, R,cnt = 0, flag;
    Student S;
    scanf("%d", &N);
    for(j = 0; j < N; j++){
        scanf("%d", &K);
        for(i = cnt; i < K+cnt; i++){
            scanf("%s %d", &S[i].IDNum, &S[i].Point);
            S[i].ExamNum = j+1;
        }
       sort(S+cnt, S+cnt+K, Compare);
       R = 1;
       flag = 0;
       S[cnt].ExamRank = R;
        for(i = 1; i < K; i++){
            if(S[cnt+i-1].Point == S[cnt+i].Point){
                flag++;
                S[cnt +i].ExamRank = R;
            }
            else{
                R += flag;
                R++;
                S[cnt + i].ExamRank = R;
                flag = 0;

            }
       }
       cnt += K;
    }
    sort(S, S+cnt, Compare);
    R = 1;
    flag = 0;
    S[0].FinalRank = R;
    for(i = 1; i < cnt; i++){
        if(S[i-1].Point == S[i].Point){
            flag++;
            S[i].FinalRank = R;
        }
        else{
            R += flag;
            R++;
            S[i].FinalRank = R;
            flag = 0;

        }
   }
   printf("%d\n", cnt);
   for(i = 0; i < cnt; i++){
       printf("%s %d %d %d\n", S[i].IDNum, S[i].FinalRank, S[i].ExamNum, S[i].ExamRank);
   }
}