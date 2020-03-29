#include<stdio.h>

int MinPrime(int R, int S){
    int p;
    if(R == 2 || R == 1)
        return 0;
    if(R % 2 == 0)
        return 2;
    if(S < 3)
        S = 3;
    for(p = S; p * p <= R; p += 2){
        if(R % p == 0)
            return p;
    }
    return 0;
}

void Output(int Num, int S){
    int p = S, count = 0;
    if(Num == 1){
        return;
    }
    if(!MinPrime(Num, S)){
        printf("%d",Num);
        return;
    }
    while(p <= Num){
        p = MinPrime(Num, p);
        if(Num % p == 0)
            break;
    }
    while(Num % p == 0){
        Num /= p;
        count++;
    }
    if(Num == 1){
        if(count > 1)
            printf("%d^%d", p, count);
        else
            printf("%d", p);
        Output(Num, p);
    }
    else{
        if(count > 1)
            printf("%d^%d*", p, count);
        else
            printf("%d*", p);
        Output(Num, p);  
    }
}
int main(){
    int test;
    scanf("%d", &test);
    printf("%d=", test);
    if(test == 1)
        printf("%d", test);
    else
        Output(test, 3);
}