#include<stdio.h>
#include<stdlib.h>
int Merge(int A[], int B[],int Left, int Mid, int Right){
    int Tmp, i , LeftEnd;
    LeftEnd = Mid - 1;
    Tmp = Right/2;
    i = 0;
    while((Left <= LeftEnd) && (Mid <= Right)){
        if(i <= Tmp){
            if(A[Left] <= A[Mid]){
                B[i] = A[Left];
                i++;
                Left++;
            }
            else{
                B[i] = A[Mid];
                i++;
                Mid++;
                }  
        }
        else
            break;
    }
    return B[i - 1];
}

int main(){
    int N, *A,* B, Num, i, j;
    scanf("%d", &N);
    A = (int *)malloc(sizeof(int) * 2 * N);
    B = (int *)malloc(sizeof(int) * 2 * N);
    for(i = 0; i < 2 * N; i++){
        scanf("%d", &A[i]);
    }
    Num = Merge(A, B, 0 , N, 2*N-1);
    printf("%d", Num);
}