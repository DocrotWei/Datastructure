#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAXS 11/*电话号码长度*/
#define MAXD 5//关键字长度
#define MAXSIZE 1000000
/*--------------------散列抽象数据结构------------------*/
typedef char ElementType[MAXS + 1];/*字符串中最后一个为结束符号*/


typedef struct HashNode *HashEntry; 
struct HashNode{
    ElementType TelePhoneNum;//存放元素
    HashEntry Next;
    int Count;
};


struct HNode{
    int TableSize;
    HashEntry Head;
};
typedef struct HNode *HashTable;
/*---------------------------------------------------------*/

int Hash(int Key, HashTable H){
    return Key % H->TableSize;
}

HashEntry Find(ElementType Key, HashTable H){
    int Pos;
    HashEntry P;
    Pos = Hash(atoi(Key + MAXS - MAXD), H);
    P = H->Head[Pos].Next;
    while(P && strcmp(P->TelePhoneNum ,Key))
        P = P->Next;
    return P;
}

void Insert(ElementType Key, HashTable H){
    HashEntry P,NewCell;
    int pos;
    P = Find(Key, H);
    if(!P)/*可以插入*/{
        NewCell = (HashEntry)malloc(sizeof(struct HashNode));
        strcpy(NewCell->TelePhoneNum, Key);
        NewCell->Count = 1;
        pos = Hash(atoi(Key + MAXS - MAXD), H);
        NewCell->Next = H->Head[pos].Next;
        H->Head[pos].Next = NewCell;
    }
    else{
        P->Count++;
    }
}

int NextPrime(int Num){
    int p = (Num % 2) ? Num+2 : Num+1, i; //找到下一个奇数
    while(p < MAXSIZE){ 
        for(i = (int)sqrt(p); i > 2; i--){
            if(!(p % i))
                break;
        }
        if(i == 2)
            break;
        else{
            p += 2;
        }
    }
    return p;
}

HashTable InitializeHashTable(int TableSize){
    HashTable H;
    int TSize;
    H = (HashTable)malloc(sizeof(struct HNode));
    TSize = NextPrime(TableSize);
    H->TableSize = TSize;
    H->Head = (HashEntry)malloc(sizeof(struct HashNode) * TSize);
    while(TSize){
        TSize--;
        H->Head[TSize].Count = 0;
        H->Head[TSize].Next = NULL;
        H->Head[TSize].TelePhoneNum[0] = '\0';
    }
    return H;
}

void ScanAndOutput(HashTable H){
    int MaxTime = 0;
    int Pnt;
    ElementType MinNum;
    HashEntry P;
    for(int i = 0; i < H->TableSize; i++){
        P = H->Head[i].Next;
        while(P){
            if(P->Count > MaxTime){
                MaxTime = P->Count;
                strcpy(MinNum, P->TelePhoneNum);
                Pnt = 1;
            }
            else if(P->Count == MaxTime){
                Pnt++;
                if(strcmp(MinNum, P->TelePhoneNum) > 0)
                    strcpy(MinNum, P->TelePhoneNum);
            }
            P = P->Next;
        }
    }

    printf("%s %d", MinNum, MaxTime);
    if(Pnt > 1)
        printf(" %d", Pnt);   
}

int main(){
    int TableSize;
    HashTable H;
    ElementType Key;
    scanf("%d", &TableSize);
    H = InitializeHashTable(TableSize);
    for(int i = 0; i < TableSize; i++){
        scanf("%s", &Key);
        Insert(Key, H);
        scanf("%s", &Key);
        Insert(Key, H);
    }
    ScanAndOutput(H);
    return 0;
}