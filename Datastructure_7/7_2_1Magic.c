#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef  int ElementType;
#define Cutoff 3
void InsertionSort(ElementType A[], int N){
    int i, j, Temp;
    for(i = 1; i < N; i++){
        Temp = A[i];
        for(j = i; j > 0 && A[j-1] < Temp; j--)
            A[j] = A[j - 1];
        A[j] = Temp;
    }
}
void Swap(ElementType *A, ElementType *B){
    ElementType Temp;
    Temp = *A;
    *A = *B;
    *B = Temp;
}
 
ElementType Median3( ElementType A[], int Left, int Right ) {      
    int Center = (Left+Right) / 2;     
    if ( A[Left] < A[Center] )         
        Swap( &A[Left], &A[Center] );     
    if ( A[Left] < A[Right] )         
        Swap( &A[Left], &A[Right] );     
    if ( A[Center] < A[Right] )         
        Swap( &A[Center], &A[Right] );     /* 此时A[Left] <= A[Center] <= A[Right] */    
    Swap( &A[Center], &A[Right-1] ); /* 将基准Pivot藏到右边*/     /* 只需要考虑A[Left+1] … A[Right-2] */     
    return  A[Right-1];  /* 返回基准Pivot */ 
} 

void Qsort( ElementType A[], int Left, int Right ) { /* 核心递归函数 */
    int Pivot, Low, High;             
    if ( Cutoff <= Right-Left ) { /* 如果序列元素充分多，进入快排 */
        Pivot = Median3( A, Left, Right ); /* 选基准 */         
        Low = Left; High = Right-1;          
        while (1) { /*将序列中比基准小的移到基准左边，大的移到右边*/               
            while ( A[++Low] > Pivot ) ;                
            while ( A[--High] < Pivot ) ;                
            if ( Low < High ) 
                Swap( &A[Low], &A[High] );                
            else break;           
        }           
    Swap( &A[Low], &A[Right-1] );   /* 将基准换到正确的位置 */            
    Qsort( A, Left, Low-1 );    /* 递归解决左边 */            
    Qsort( A, Low+1, Right );   /* 递归解决右边 */        
    }      
    else 
        InsertionSort( A+Left, Right-Left+1 ); /* 元素太少，用简单排序 */  
} 

void QuickSort( ElementType A[], int N ) { 
    /* 统一接口 */      
    Qsort( A, 0, N-1 ); 
}

int main(){
    int i, N, M, *Money, *Count, Sum = 0;
    int s1 = 0, s2 = 0, f1 = 0, f2 = 0;

    scanf("%d", &N);
    Money = (int *)malloc(sizeof(int) * N);
    memset(Money, 0,  N);
    for(i = 0; i < N; i++)
        scanf("%d", &Money[i]);

    scanf("%d", &M);
    Count = (int *)malloc(sizeof(int) * M);
    memset(Count, 0, M);
    for(i = 0; i < M; i++)
        scanf("%d", &Count[i]);
    QuickSort(Money, N);
    QuickSort(Count, M);
    s1 = s2 = 0;
    f1 = N - 1;
    f2 = M - 1;

    while((s1 <= f1) && (s2 <= f2)){
        if(Money[s1] * Count[s2] > 0){
            Sum += Money[s1]* Count[s2];
            s1++;
            s2++;
        }
        else break;
    }
    while((s1 <= f1) && (s2 <= f2)){
        if(Money[f1] * Count[f2] > 0){
            Sum += Money[f1]* Count[f2];
            f1--;
            f2--;
        }
        else break;
    }

    printf("%d", Sum);
}



