#include<stdio.h>
#include<math.h>
#define MAXSIZE 10000

int main(){
    int A[MAXSIZE], N;
    double Avg = 0,Varience = 0, varience[MAXSIZE];
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
        Avg += A[i];
    }
    Avg = Avg / N;
    for(int i = 0; i < N; i++){
        varience[i] = (A[i] - Avg) * (A[i] - Avg);
        Varience += varience[i];
    } 
    Varience = sqrt(Varience / N);
    printf("%.5f", Varience);
}