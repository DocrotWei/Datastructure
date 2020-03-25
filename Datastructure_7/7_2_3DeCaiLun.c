#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MaxIDNum 8
#define MaxSize 100000
typedef char IDNumType[MaxIDNum + 1];
struct SNode{
    IDNumType IDNum;
    int DePoint;
    int CaiPoint;
    int Sum;
};

typedef struct SNode *Student;

#define Cutoff 100000
void InsertionSort(Student S, int A[], int N){
    int i, j, Temp, pos;
    for(i = 1; i < N; i++){
        pos = A[i];
        j = i;
        for(;j > 0 && (S[A[j-1]].Sum <= S[pos].Sum);j--){
            if(S[A[j-1]].Sum == S[pos].Sum){
                if(S[A[j-1]].DePoint < S[pos].DePoint){
                    A[j] = A[j-1];
                }
                else if((S[A[j-1]].DePoint == S[pos].DePoint)&& (strcmp(S[A[j-1]].IDNum, S[pos].IDNum) > 0)){
                        A[j] = A[j-1];
                }
                else
                    break;
            }
            else{
                A[j] = A[j-1];
            }
        }
        A[j] = pos;
    }
}
void Swap(int *A, int *B){
    int Temp;
    Temp = *A;
    *A = *B;
    *B = Temp;
}
 
int Median3( int A[], Student S, int Left, int Right ) {      
    int Center = (Left+Right) / 2;     
    if ( S[A[Left]].Sum < S[A[Center]].Sum )         
        Swap( &A[Left], &A[Center] );     
    if ( S[A[Left]].Sum < S[A[Right]].Sum )         
        Swap( &A[Left], &A[Right] );     
    if ( S[A[Center]].Sum < S[A[Right]].Sum )         
        Swap( &A[Center], &A[Right] );     /* 此时A[Left] <= A[Center] <= A[Right] */    
    Swap( &A[Center], &A[Right-1] ); /* 将基准Pivot藏到右边*/     /* 只需要考虑A[Left+1] … A[Right-2] */     
    return  A[Right-1];  /* 返回基准Pivot */ 
} 

void Qsort(int A[], Student S, int Left, int Right ) { /* 核心递归函数 */
    int Pivot, Low, High;             
    if ( Cutoff <= Right-Left ) { /* 如果序列元素充分多，进入快排 */
        Pivot = S[Median3( A, S,Left, Right )].Sum; /* 选基准 */         
        Low = Left; High = Right-1;          
        while (1) { /*将序列中比基准小的移到基准左边，大的移到右边*/               
            while ( S[A[++Low]].Sum > Pivot ) ;                
            while ( S[A[--High]].Sum < Pivot ) ;                
            if ( Low < High ) 
                Swap( &A[Low], &A[High] );                
            else break;           
        }           
    Swap( &A[Low], &A[Right-1] );   /* 将基准换到正确的位置 */            
    Qsort( A, S, Left, Low-1 );    /* 递归解决左边 */            
    Qsort( A, S, Low+1, Right );   /* 递归解决右边 */        
    }      
    else 
        InsertionSort(S, A+Left, Right-Left+1); /* 元素太少，用简单排序 */  
} 

void QuickSort( int A[], Student S, int N ) { 
    /* 统一接口 */      
    Qsort( A, S, 0, N-1 ); 
}

void PrintSort(Student S, int A[], int N){
    int i = 0;
    for(i = 0; i < N; i++)
        printf("%s %d %d\n", S[A[i]].IDNum, S[A[i]].DePoint, S[A[i]].CaiPoint);
}

int main(){
    int N, L, H, i;
    int Class1[MaxSize], Class2[MaxSize], Class3[MaxSize], Class4[MaxSize];
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0, sum = 0;
    Student S;
    memset(Class1, 0, sizeof(int) * MaxSize);
    memset(Class2, 0, sizeof(int) * MaxSize);
    memset(Class3, 0, sizeof(int) * MaxSize);
    memset(Class4, 0, sizeof(int) * MaxSize);
    scanf("%d %d %d", &N, &L, &H);
    S = (Student)malloc(sizeof(struct SNode) * N);
    for(i = 0; i < N; i++){
        scanf("%s %d %d", S[i].IDNum, &S[i].DePoint, &S[i].CaiPoint);
        S[i].Sum = S[i].DePoint + S[i].CaiPoint;
        if(S[i].DePoint >= L && S[i].CaiPoint >= L){
            if(S[i].DePoint >= H && S[i].CaiPoint >= H){
                Class1[i1++] = i;
                sum++;
            }
            else if(S[i].DePoint >=H && S[i].CaiPoint < H){
                Class2[i2++] = i;
                sum++;
            }
            else if(S[i].DePoint < H && S[i].CaiPoint < H && S[i].DePoint >= S[i].CaiPoint){
                sum++;
                Class3[i3++] = i;
            }
            else{
                sum++;
                Class4[i4++] = i;
            }
        }
    }
    printf("%d\n", sum);
    QuickSort(Class1, S, i1);
    QuickSort(Class2, S, i2);
    QuickSort(Class3, S, i3);
    QuickSort(Class4, S, i4);
    PrintSort(S, Class1, i1);     
    PrintSort(S, Class2, i2);   
    PrintSort(S, Class3, i3);   
    PrintSort(S, Class4, i4);   
}