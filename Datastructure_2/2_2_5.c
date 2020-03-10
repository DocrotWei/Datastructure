#include<stdio.h>
#define MAXN 30

int N;
int Terms[30];
int Count;

/*Remainder 为剩余得数， Start为开始得数， nTerm为到达了第几层*/
void Search(int Remainder, int Start, int nTerm){
    int i;
    for(i = Start; i <= Remainder; i++){
        if(Remainder - i >= i){
            Terms[nTerm] = i;
            Search(Remainder - i, i, nTerm + 1);
        }
        if(Remainder - i == 0){
            Terms[nTerm] = i;
            Count++;
            if(Count % 4 != 1)
                printf(";");
            printf("%d=%d", N, Terms[0]);
            for(int j = 1; j < nTerm + 1; j++){
                printf("+%d", Terms[j]);
            }
            if(Count % 4 == 0)
                printf("\n");
        }
    }
}

int main(){
    scanf("%d", &N);
    Count = 0;
    Search(N, 1, 0);
    return 0;
}