#include<stdio.h>
#include<string.h>
#define MAXSZIE 10
int main(){
    int  N, Sum, test[MAXSZIE];
    memset(test, 0, sizeof(test));
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", &test[i]);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i != j)
                Sum += test[i] * 10 + test[j];
        }
    }
    printf("%d", Sum);
}