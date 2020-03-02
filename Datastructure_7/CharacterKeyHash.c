#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXS 8//字符串长度
#define MAXB 5//每个字符占的位置
#define MAXD 3//关键字长度
#define Mask ((1<<(MAXD * MAXB)) - 1)//掩码
/*--------------------散列抽象数据结构------------------*/
typedef char ElementType[MAXS + 1];/*字符串中最后一个为结束符号*/
enum EntryType {Legitimate, Empty};//Empty 为无人占用

struct HashEntry{
    ElementType Element;//存放元素
    enum EntryType Info;//Occupation Sign
};

struct HNode{
    int TableSize;
    struct HashEntry *TheCells;
};
typedef struct HNode *HashTable;
/*----------------------------------------------------*/
/*--------------------散列表相关函数-------------------*/
HashTable InitializeHashTable(int TableSize){
    HashTable H;
    H = (HashTable)malloc(sizeof(struct HNode));
    H->TableSize = TableSize;
    H->TheCells = (struct HashEntry*)malloc(sizeof(struct HashEntry) * TableSize);
    while(TableSize)
        H->TheCells[--TableSize].Info = Empty;
    return H;
}

int Hash(ElementType Key, HashTable H){
    int pos = 0;
    while(*Key != '\0')
        pos = (pos << MAXB) + (*Key++ - 'A');
    return ((pos & Mask) % H->TableSize);
}

int FindPos(ElementType Key, HashTable H){
    int Next,Pos = Hash(Key, H), cnt = 0;
    Next = Pos;
    while((H->TheCells[Next].Info != Empty) && strcmp(Key, H->TheCells[Next].Element)){
        if(++cnt % 2){
            Next = Pos + (((cnt+1) * (cnt+1))>>2);
            if(Next >= H->TableSize)
                Next -= H->TableSize;
        }
        else
        {
            Next = Pos - ((cnt * cnt)>>2);
            if(Next < 0)
                Next += H->TableSize;
        }
    }
    return Next;
}

void InsertAndOutput(ElementType Key, HashTable H){
    int Pos;
    Pos = FindPos(Key, H);
    if(H->TheCells[Pos].Info == Empty){
        H->TheCells[Pos].Info = Legitimate;
        strcpy(H->TheCells[Pos].Element, Key);
    }
    printf("%d", Pos);
}


int main(){
    HashTable H;
    int N,TableSize;
    ElementType Key;
    scanf("%d %d", &N, &TableSize);
    H = InitializeHashTable(TableSize);
    scanf("%s", Key);
    InsertAndOutput(Key, H);
    for(int i = 1; i < N; i++){
        scanf("%s", Key);
        printf(" ");
        InsertAndOutput(Key, H);
    }
    return 0;
}
