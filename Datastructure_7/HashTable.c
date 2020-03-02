#include<stdio.h>
#include<stdlib.h>

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

HashTable InitializeTable(int TableSize){
    HashTable H = (HashTable)malloc(sizeof(struct HNode));
    H->TableSize = TableSize;
    H->TheCells = (struct HashEntry*)malloc(sizeof(struct HashEntry) * TableSize);
    while(TableSize){
        H->TheCells[--TableSize].Info = Empty;
    }
    return H;
}

int Hash(ElementType Key, HashTable H){
    return Key % H->TableSize;
}

int Find(ElementType Key, HashTable H){
    int pos;
    pos = Hash(Key, H);
    while((H->TheCells[pos].Info != Empty) && (H->TheCells[pos].Element != Key)){//第一个是
        pos++;
        if(pos == H->TableSize)
            pos -= H->TableSize;
    }
    return pos;
}

void InsertAndOutput(ElementType Key, HashTable H){
    int pos = Find(Key, H);
    if(H->TheCells[pos].Info == Empty){
        H->TheCells[pos].Element = Key;
        H->TheCells[pos].Info = Legitimate;
    }
    printf("%d", pos);
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
        scanf("%d ", &Key);
        printf(" ");
        InsertAndOutput(Key, H);
    }
    return 0;
}