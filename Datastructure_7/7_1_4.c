#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 51
#define MaxSzie 100000

int Compare(const void*a, const void*b){
    return *(int *)a - *(int *)b;  
}
int main(){
    int N, i, Count[MaxSzie], Workage, cnt, flag = 0;
    scanf("%d", &N);
    int temp = -1;
    for(i = 0; i < N; i++){
        scanf("%d", &Workage);
        Count[i] = Workage;
    }
    qsort(Count, N, sizeof(int), Compare);
    for(i = 0; i < N; i++){
        if(Count[i] != temp){
            if(flag)
                printf(":%d\n", cnt);
            else 
            flag = 1;
            temp = Count[i];
            printf("%d", temp);
            cnt = 1;
        }
        else{
            cnt++;
        }
    }
    printf(":%d\n", cnt);
    /*int N, i, Count[MAX], Workage;
    memset(Count, 0, sizeof(int) * MAX);
    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%d", &Workage);
        if(Workage <= (MAX - 1))
            Count[Workage]++;
    }
    for(i = 0; i < MAX; i++)
        if(Count[i] != 0)
            printf("%d:%d\n", i, Count[i]);*/
}

