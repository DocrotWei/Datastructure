#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;

void Adjust(ElementType A[], int i, int Size){
    ElementType Temp;
    int Child, Parent;
    Parent = i;
    for(Temp = A[Parent]; (2 * Parent + 1) < Size; Parent = Child){
        Child = 2 * Parent + 1;
        if((Child != Size-1) && A[Child+1] > A[Child])
            Child++;
        if(Temp < A[Child])
            A[Parent] = A[Child];
        else
            break;
    }
    A[Parent] = Temp;
}

void NextHeapSort(ElementType A[], int N){
    int i;
    ElementType temp;
    for(i = 1; i <= N; i++)
        if(A[i] > A[0])
            break;

        temp = A[0];
        A[0] = A[i-1];
        A[i-1] = temp;
        Adjust(A, 0, i-1);
}


/*输入： Origin为原始数组 Test为中间得数组 N为元素个数 输出： 如果是插入排序则返回位置 如果是归并排序返回 0*/
int Judge(int Test[], int Origin[], int N){
    /*主要思想就是如果是插入排序前面得为有序后面得与原序列相同*/
    /*分析时要考虑特殊情况，例如如果w没有符合都是有序得要求得，所以这个时候就有了需要一个判断标志来标志是否一次比较多没有成功*/
    int i, flag = 0, pos;//pos是用来记录有序得位置得
    for(i = 1; i < N; i++){
        if(Test[i] >= Test[i - 1]){
            flag = 1;
        }
        else{
            pos = i;
            break;
        }
    }

    if(flag == 0)
        return 0;

    for(i = pos; i < N; i++){
        if(Test[i] != Origin[i])
            return 0;
    }

    return pos;
}

/*输入： Test为输入数组 N为排序元素得总个数 Pos为有序元素得截止标识*/
void NextInsertionSort(int Test[], int N, int Pos){
    int i, Temp;//抽下一张牌
    Temp = Test[Pos];
    for(i = Pos; i < N && Test[i - 1] > Temp; i--)
        Test[i] = Test[i - 1];
    Test[i] = Temp;
}


void Output(int output[], int Flag, int N){
    int flag = 0;
    if(Flag == 0)
        printf("Heap Sort\n");
    else
        printf("Insertion Sort\n");
    for(int i = 0; i < N; i++){
        if(flag == 0){
            printf("%d", output[i]);
            flag = 1;
            }
        else
            printf(" %d", output[i]);
    }
}

int main(){
    int N, *Origin, *Test, i, flag;
    scanf("%d", &N);
    Origin = (int *)malloc(sizeof(int) * N);
    Test = (int *)malloc(sizeof(int) * N);
    for(i = 0; i < N; i++)
        scanf("%d", &Origin[i]);
    for(i = 0; i < N; i++)
        scanf("%d", &Test[i]);
    flag = Judge(Test, Origin, N);
    if(flag == 0){
        NextHeapSort(Test, N);
        Output(Test, flag, N);
    }
    else{
        NextInsertionSort(Test, N, flag);
        Output(Test, flag, N);
    }
}