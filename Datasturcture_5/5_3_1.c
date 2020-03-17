#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAXIDCARD 18
#define MAXSIZE 3000000

/*--------------------散列抽象数据结构------------------*/
typedef char IDCardType [MAXIDCARD + 1];/*字符串中最后一个为结束符号*/
typedef int MileType;

typedef struct HashNode *HashEntry; 
struct HashNode{
    IDCardType IDCard;//存放元素
    MileType mile;
    HashEntry Next;
};


struct HNode{
    int TableSize;
    HashEntry TheCells;
    MileType MinMile;
};
typedef struct HNode *HashTable;

int Hash(int key, HashTable H){
    return key % H->TableSize;
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

HashTable InitializeHashTable(int TableSize, MileType MinMile){
    HashTable H;
    int TSize;
    H = (HashTable)malloc(sizeof(struct HNode));
    while(NextPrime(TableSize) && ((TableSize - 3) % 4 != 0))
        TableSize++;
    TSize = TableSize;
    H->TableSize = TSize;
    H->MinMile = MinMile;
    H->TheCells = (HashEntry)malloc(sizeof(struct HashNode) * TSize);
    while(TSize){
        TSize--;
        H->TheCells[TSize].mile = 0;
        H->TheCells[TSize].IDCard[0] = '\0';
        H->TheCells[TSize].Next = NULL; 
    }
    return H;
}

int GetNum(IDCardType IDNum){
    int H;
    H = (IDNum[10] - '0') * 10 + (IDNum[12] - '0');
    H = H * 10 + (IDNum[14] - '0');
    H = H * 10 + (IDNum[16] - '0');
    H = H * 10 + (IDNum[17] - '0');
    H = H * 10 + (IDNum[18] == 'x') ? 10 : ( IDNum[18] - '0');
    return H;
}

void FindAndInsert(IDCardType IDNum, int Mile, HashTable H){
    int Pos;
    HashEntry P, NewNode;
    Pos = GetNum(IDNum);
    Pos = Hash(Pos, H);
    P = H->TheCells[Pos].Next;
    while(P && strcmp(P->IDCard, IDNum))
        P = P->Next;
    if(!P){
                /*如果为空的化建立新的空间并插入*/
        NewNode = (HashEntry)malloc(sizeof(struct HashNode));
        strcpy(NewNode->IDCard, IDNum);
        if(Mile < H->MinMile)
            NewNode->mile = H->MinMile;
        else
            NewNode->mile = Mile;
        NewNode->Next = H->TheCells[Pos].Next;
        H->TheCells[Pos].Next = NewNode;
    }
    else
        if(Mile < H->MinMile)
            P->mile += H->MinMile;
        else
            P->mile += Mile;
}

void FindAndCheck(IDCardType IDNum, HashTable H){
    int Pos;
    HashEntry P, NewNode;
    Pos = GetNum(IDNum);
    Pos = Hash(Pos, H);
    P = H->TheCells[Pos].Next;
    while(P && strcmp(P->IDCard, IDNum))
        P = P->Next;
    if(!P){
        printf("No Info\n");
    }
    else
        printf("%d\n", P->mile);
}


int main(){
    HashTable H;
    IDCardType IDNum;
    int TableSize, minMile, N, mile;
    scanf("%d %d", &TableSize, &minMile);
    N = TableSize;
    H = InitializeHashTable(TableSize, minMile);
    for(int i = 0; i < N; i++){
        scanf("%s %d", &IDNum, &mile);
        FindAndInsert(IDNum, mile, H);
    }
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%s", &IDNum);
        FindAndCheck(IDNum, H);
    }
}