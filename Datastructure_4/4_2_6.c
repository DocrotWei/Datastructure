#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxSize 260 
typedef char FilePathType[MaxSize + 1];

typedef struct TNode *Tree;
struct TNode{
    char *Name;
    int IsCatalog;
    Tree Child;
    Tree File;
    Tree Brother;
};

Tree NewNode(char *K){
    Tree Tnode = (Tree)malloc(sizeof(struct TNode));
    Tnode->Name = (char*)malloc(sizeof(char) * (strlen(K) + 1));
    Tnode->Brother = Tnode->Child = Tnode->File = NULL;
    Tnode->IsCatalog = 1;
    strcpy(Tnode->Name, K);
    return Tnode;
}

Tree InsertCatalog(Tree T, char Name[]){
    if(!T || strcmp(T->Name, Name) > 0){
        Tree newNode = NewNode(Name);
        newNode->Brother = T;
        return newNode;
    }
    if(!strcmp(T->Name, Name))/*目录输入一共可以是n次，这n次前面得文件明可能是一致的后面的不同*/
        return T;
    T->Brother = InsertCatalog(T->Brother, Name);
    return T;
}

Tree InsertFile(Tree T, char Name[]){//注意返回的都应该是表头地址
    if(!T || strcmp(T->Name, Name) > 0){
        Tree newNode = NewNode(Name);
        newNode->IsCatalog = 0;
        newNode->Brother = T;
        return newNode;
    }
    //if(!strcmp(T->Name, Name)文件只可能输入一次，建立一个文件
    T->Brother = InsertFile(T->Brother, Name);
    return T;
}

void ReadPath(Tree T){
    FilePathType Filepath, Name;
    scanf("%s", Filepath);
    int l, j, s = 0;;//s是用来记住起点的位置的
    for(l = 0; l < strlen(Filepath); l++){
        if(Filepath[l] == '\\'){
            for(j = s; j < l; j++)
                Name[j - s] = Filepath[j];
            Name[l - s] = '\0';
            s = l + 1;//改变起始位置
            T->Child =InsertCatalog(T->Child, Name);
            T = T->Child;
            while(strcmp(T->Name, Name) != 0)
                T = T->Brother;
        }
    }
    if(s < strlen(Filepath)){
        for(j = s; j <= strlen(Filepath); j++)
            Name[j - s] = Filepath[j];
        T->File = InsertFile(T->File, Name);
        }
}

void PrintCatalog(Tree T, int Space){
    if(T){
        for(int i = 0; i < Space; i++)
            printf(" ");
        printf("%s\n", T->Name);
        if(T->IsCatalog == 1)//代表他可能有子目录
            PrintCatalog(T->Child, Space + 2);
        PrintCatalog(T->File, Space + 2);
        PrintCatalog(T->Brother, Space);
    }
}

int main(){
    int N;
    Tree Root;
    scanf("%d", &N);
    Root = (Tree)malloc(sizeof(struct TNode));
    Root->Brother = Root->Child = Root->File = NULL;
    Root->Name = (char*)malloc(sizeof(char) * 5);
    strcpy(Root->Name, "root");
    Root->IsCatalog = 1;
    for(int i = 0; i < N; i++){
        ReadPath(Root);
    }
    PrintCatalog(Root, 0);
    return 0;
    }