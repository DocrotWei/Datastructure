#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*-------------散列表定义-----------*/
typedef int ElementType;
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
/*-------------------------------------*/

int IsPrime(int Num){/*返回1为素数， 返回0为非素数*/
    int i;
    for(i = 2; i <= sqrt(Num); i++){
        if((Num % i) == 0)
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

HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct HNode));
    if(IsPrime(TableSize))
        H->TableSize = TableSize;
    else
        H->TableSize = FindPrime(TableSize);
    H->TheCells = (struct HashEntry*)malloc(sizeof(struct HashEntry) * TableSize);
    while(TableSize){
        H->TheCells[--TableSize].Info = Empty;
    }
    return H;
}



int Hash(ElementType Key, HashTable H){
    return Key % H->TableSize;
}

int FindPos(ElementType Key, HashTable H){
    int Next,Pos = Hash(Key, H), cnt = 0, j;
    Next = Pos;
    while((H->TheCells[Next].Info != Empty) && (Key ==  H->TheCells[Next].Element)){
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
        j++;
        if(j == H->TableSize)
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
    if(H->TheCells[pos].Info == Empty){
        H->TheCells[pos].Element = Key;
        H->TheCells[pos].Info = Legitimate;
        printf("%d", pos);
    }
}

int main(){
    HashTable H;
    int TableSize, Num;
    ElementType Key;
    scanf("%d %d", &Num, &TableSize);
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