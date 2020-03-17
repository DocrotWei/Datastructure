#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSchoolNum 6
#define MaxNameNum 8
#define MaxGradeNum 3
#define MaxSize 100000

struct Strudent{
    char SchoolNUm[MaxSchoolNum + 1];
    char Name[MaxNameNum + 1];
    int Grade;
}Record[MaxSize];
typedef struct Strudent *PtrToStudent;

int CompareSchoolNum(const void *a, const void *b){
    return strcmp(((const PtrToStudent)a)->SchoolNUm, ((const PtrToStudent)b)->SchoolNUm);//const void* 代表一个可以指向任意类型的指针，但不可以修改值得大小
}
 
int CompareName(const void *a, const void *b){
    int k;
    k = strcmp(((const PtrToStudent)a)->Name, ((const PtrToStudent)b)->Name);
    if(!k)
        k = strcmp(((const PtrToStudent)a)->SchoolNUm, ((const PtrToStudent)b)->SchoolNUm);
    return k;
}
int CompareGrade(const void* a, const void* b) {//因为成绩得字符串数目不是个定值所以不好用字符串比较
	int k = (((const PtrToStudent)a)->Grade > ((const PtrToStudent)b)->Grade)? 1 : 0;
	if (!k) {
		k = (((const PtrToStudent)a)->Grade < ((const PtrToStudent)b)->Grade) ? -1 : 0;
		if (!k)
			k = strcmp(((const PtrToStudent)a)->SchoolNUm, ((const PtrToStudent)b)->SchoolNUm);
	}
	return k;
}

int main(){
    int N, C, i;
    scanf("%d %d", &N, &C);
    for(i = 0; i < N; i++)
        scanf("%s %s %d", Record[i].SchoolNUm, Record[i].Name, &Record[i].Grade);//给数组赋值都是这样嘛？
    switch (C)
    {
    case 1:
        qsort(Record, N, sizeof(struct Strudent), CompareSchoolNum);
        break;
    case 2:
        qsort(Record, N, sizeof(struct Strudent), CompareName);
        break;
    case 3:
        qsort(Record, N, sizeof(struct Strudent), CompareGrade);
        break;
    }
    for(i = 0; i < N; i++)
        printf("%s %s %d\n", Record[i].SchoolNUm, Record[i].Name, Record[i].Grade);

}