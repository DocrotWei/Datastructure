#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAXQNUM 10/*电话号码长度*/
#define MAXQCODE 16
#define MAXSIZE 300000

/*--------------------散列抽象数据结构------------------*/
typedef char QQNumType[MAXQNUM + 1];/*字符串中最后一个为结束符号*/
typedef char QQCodeType[MAXQCODE + 1];/*字符串中最后一个为结束符号*/

typedef struct HashNode *HashEntry; 
struct HashNode{
    QQNumType QQNum;//存放元素
    QQCodeType QQCode;
    char Info;
};


struct HNode{
    int TableSize;
    HashEntry TheCells;
};
typedef struct HNode *HashTable;
/*-----------------------------------------------------------*/

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
    while(NextPrime(TableSize) && ((TableSize - 3) % 4 != 0))
        TableSize++;
    TSize = TableSize;
    H->TableSize = TSize;
    H->TheCells = (HashEntry)malloc(sizeof(struct HashNode) * TSize);
    while(TSize){
        TSize--;
        H->TheCells[TSize].QQCode[0] = '\0';
        H->TheCells[TSize].QQNum[0] = '\0';
        H->TheCells[TSize].Info = 0;
    }
    return H;
}

int Hash(int Key, HashTable H){

    return Key % H->TableSize;
}

int NewFindPos(QQNumType QNum, HashTable H){
    int Next,Pos, cnt = 0;
    QQNumType Key;
    if(QNum[4] == '\0' || QNum[5] == '\0')
        strcpy(Key, QNum);
    else 
        strncpy(Key, QNum+1, 5);
    Pos = Hash(atoi(Key), H);
    Next = Pos;

    while((H->TheCells[Next].Info != 0) && strcmp(QNum, H->TheCells[Next].QQNum)){
        if(++cnt % 2){
            Next = Pos + (((cnt+1) * (cnt+1))>>2);
            while(Next >= H->TableSize)
                Next -= H->TableSize;
        }
        else{
            Next = Pos - ((cnt * cnt)>>2);
            while(Next < 0)
                Next += H->TableSize;
        }
    }
    return Next;
}

void NewQQ(QQNumType QNum, QQCodeType QCode, HashTable H){
    int Pos;
    Pos = NewFindPos(QNum, H);
    if(H->TheCells[Pos].Info == 0){
        H->TheCells[Pos].Info = 1;
        strcpy(H->TheCells[Pos].QQNum, QNum);
        strcpy(H->TheCells[Pos].QQCode, QCode);
        printf("New: OK\n");
    }
    else
        printf("ERROR: Exist\n");
}

int LoadFindPos(QQNumType QNum, HashTable H){
    int Next,Pos, cnt = 0;
    int Pnt;
    QQNumType Key;
    if(QNum[4] == '\0' || QNum[5] == '\0')
        strcpy(Key, QNum);
    else 
        strncpy(Key, QNum+1, 5);
    Pos = Hash(atoi(Key), H);
    Next = Pos;
    while(strcmp(QNum, H->TheCells[Next].QQNum) && H->TheCells[Next].Info != 0){
        if(++cnt % 2){
            Next = Pos + (((cnt+1) * (cnt+1))>>2);
            while(Next >= H->TableSize)
                Next -= H->TableSize;
        }
        else
        {
            Next = Pos - ((cnt * cnt)>>2);
            while(Next < 0)
                Next += H->TableSize;
        }
    }
    return Next;
}

void LoadQQ(QQCodeType QCode, QQNumType QNum, HashTable H){
    int Pos;
    Pos = LoadFindPos(QNum, H);
    if(H->TheCells[Pos].Info == 0){
        printf("ERROR: Not Exist\n");
        return;
    }
    if(H->TheCells[Pos].Info == 1){
        if(!strcmp(H->TheCells[Pos].QQCode, QCode)){
            printf("Login: OK\n");
            return;
        }
        else{
            printf("ERROR: Wrong PW\n");
            return;
        }
    }
}
/*---------------------------------------------------------------*/
int main(){
    HashTable H;
    int N,TSize;
    char Command;
    QQNumType QQNum;
    QQCodeType QQCode;
    scanf("%d", &N);
    TSize = N;
    H = InitializeHashTable(2 * N);
    for(int i = 0; i < TSize; i++){
        scanf("%s", &Command);
        switch (Command)
        {
            case 'N':
                scanf("%s %s", &QQNum, &QQCode);
                NewQQ (QQNum, QQCode, H);
                break;
            case 'L':
                scanf("%s %s", &QQNum, &QQCode);
                LoadQQ (QQCode, QQNum, H);
                break;
        }
    }
    return 0;
}
