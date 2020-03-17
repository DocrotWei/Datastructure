#include<stdio.h>
#include<stdlib.h>

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

void Merge(int Test[], int Tmp[], int Left, int Right, int RightEnd){
    int LeftEnd = Right - 1 ,Num;
    int t;
    Num = RightEnd - Left;
    t = Left;
    while((Left <= LeftEnd) && (Right <= RightEnd)){
        if(Test[Left] <= Test[Right])
            Tmp[t++] = Test[Left++];
        else
            Tmp[t++] = Test[Right++];
    }
    while(Left <= LeftEnd)
        Tmp[t++] = Test[Left++];
    while (Right <= RightEnd)
        Tmp[t++] = Test[Right++];
    for(int i = Num; i >= 0; i--){
        Test[RightEnd] = Tmp[RightEnd];
        RightEnd--;
    }

}

int FindLength(int Test[], int N){//这个不能从头比，要比段与段之间得接口处，返回得值就是现在有序得段得值
    int i, j;
    for(j = 2; j <= N; j *= 2){
        for(i = j; i < N; i += 2*j)
            if(Test[i - 1] > Test[i])
                break;
        if(i < N)
            break;
    }
    return j;
}

void NextMergeSort(int Test[], int N){
    int length = FindLength(Test, N),i;
    int *Tmp;
    Tmp = (int*)malloc(sizeof(int) * N);
    for(i = 0; i <= N-2*length; i += 2 * length)
        Merge(Test, Tmp, i, i + length, 2 * length + i - 1);
    if(i + length < N)
        Merge(Test, Tmp, i, i + length, N-1);
}

void Output(int output[], int Flag, int N){
    int flag = 0;
    if(Flag == 0)
        printf("Merge Sort\n");
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
        NextMergeSort(Test, N);
        Output(Test, flag, N);
    }
    else{
        NextInsertionSort(Test, N, flag);
        Output(Test, flag, N);
    }
}