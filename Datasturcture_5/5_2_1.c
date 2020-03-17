#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MaxSize 10007
/*-------------散列表定义-----------*/
typedef int ElementType;
enum EntryType {Legitimate, Empty};//Empty 为无人占用
typedef struct HashNode{
    ElementType Element;//存放元素
    ElementType Info;//Occupation Sign
}HashEntry[MaxSize] ;

struct HNode{
    int TableSize;
    HashEntry TheCells;
};
typedef struct HNode *HashTable;
/*-------------------------------------*/
/*---------------寻找素数部分-----------*/
int IsPrime(int Num){/*返回1为素数， 返回0为非素数*/
    int i;
    if(Num == 1 || Num == 0)
        return 0;
    if(Num == 2)
        return 1;
    for(i = 2; i <= sqrt(Num); i++){
        if((Num % (int)i) == 0)
            return 0;
    }
    return 1;
}

int FindPrime(int TableSzie){
    int Prime = TableSzie;
    while(!IsPrime(Prime)){
        Prime++;
    }
    return Prime;
}
/*------------------------------------*/

HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct HNode));
    TableSize = H->TableSize = FindPrime(TableSize);
    while(TableSize){
        H->TheCells[--TableSize].Info = 0;
        H->TheCells[TableSize].Element = 0;
    }
    return H;
}

int Hash(ElementType Key, HashTable H){
    return Key % H->TableSize;
}

int FindPos(ElementType Key, HashTable H){
    int Next,Pos = Hash(Key, H), cnt = 1;
    Next = Pos;
    while(H->TheCells[Next].Info != 0 && H->TheCells[Next].Element != Key){
        Next = Pos + ((cnt) * (cnt));
        cnt++;
        if(Next >= H->TableSize)
            Next = Next % H->TableSize;

        if(cnt == H->TableSize)
            return -1;
    }
    return Next;
}

void InsertAndOutput(ElementType Key, HashTable H){
    int pos = FindPos(Key, H);
    if(pos == -1){
        printf("-");
        return;
    }
    if(H->TheCells[pos].Info == 0){
        H->TheCells[pos].Element = Key;
        H->TheCells[pos].Info = 1;
        printf("%d", pos);
    }
}

int main(){
    HashTable H;
    int TableSize, Num;
    ElementType Key;
    scanf("%d %d", &TableSize, &Num);
    H = InitializeTable(TableSize);
    scanf("%d", &Key);
    InsertAndOutput(Key, H);
    for(int i = 1; i < Num; i++){
        scanf("%d", &Key);
        printf(" ");
        InsertAndOutput(Key, H);
    }
    return 0;
}