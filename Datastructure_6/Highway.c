#include<stdlib.h>
#include <stdio.h>
typedef int ElementType; 
#define MaxV 1000
typedef int Vertex;
typedef int WeightType; 

typedef int Disjset[MaxV + 1];
typedef struct EdgeNode *Edge;
struct EdgeNode{
    Vertex V1, V2;
    WeightType weight;
};

Disjset VSet;
Edge ESet;

/*-----------------------------------------并查集-----------------------------------------------*/
/*并查集初始化*/
void InitializeVSet(int N){
    while(N+1)
    VSet[N--] = -1; 
}

/*查找根所在的集合*/
Vertex FindRoot(Disjset S, Vertex V){
    Vertex Root, Trail, Lead;
    for(Root = V; S[Root] > 0; Root = S[Root]); //找到根节点
    /*路径压缩*/
    for(Trail = V; Trail != Root; Trail = Lead){
        Lead = S[Trail];
        S[Trail] = Root;
    }
    return Root;
}

/*并查集求并*/
void Union(Disjset S, Vertex Root1, Vertex Root2){
    if(S[Root1] < S[Root2]){
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
    else{
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

/*查看两个元素是否是一个集合的*/
int CheckCycle(Vertex V1, Vertex V2){
    Vertex Root1 = FindRoot(VSet, V1);
    Vertex Root2 = FindRoot(VSet, V2);
    if(Root1 == Root2)
        return 0;
    else{
        Union(VSet, Root1, Root2);
        return 1;
    }
}
/*-------------------------------------------------------------------------------------------*/
/*--------------------------------------最小堆-----------------------------------------------*/
/*向下过滤最小堆*/
void MinHeap(Edge E, int Parent, int Size){
    int Child;
    struct EdgeNode temp;
    temp = E[Parent];
    for(; ((Parent<<1)) < Size; Parent = Child){
        Child = (Parent << 1);
        if((Child != Size) && (E[Child].weight) > E[Child+1].weight)
            Child++;
        if(temp.weight > E[Child].weight)
            E[Parent] = E[Child];
        else
            break;
    }
    E[Parent] = temp;
}

int GetEdge(Edge E, int CurrentSize){
    struct EdgeNode Min;
    struct EdgeNode Temp;
    Min = E[1];
    Temp = E[CurrentSize--];
    E[1] = Temp;
    MinHeap(E, 1, CurrentSize);
    return CurrentSize; //返回最小位置
}
/*初始化最小堆*/
void InitializeESet(int M){
    int i;
    for(i = M/2; i > 0; i--)
        MinHeap(ESet, i, M);
}

/*---------------------------------------------------------------------------------------*/
/*最小生成树kruskal算法*/
int Krusral(int N, int M){
    int EdgeN = 0;
    int Cost = 0;
    int NextEdge = M;//下一条所在的位置
    InitializeESet(M);
    InitializeVSet(N);
    while(EdgeN < N-1){
        if(NextEdge <= 0)
            break;
        NextEdge = GetEdge(ESet, NextEdge);
        if(CheckCycle(ESet[NextEdge].V1, ESet[NextEdge].V2)){
            Cost += ESet[NextEdge].weight;
            EdgeN++;
        }
    }
    if(EdgeN < N-1)
        Cost = -1;
    return Cost;
}

int main(){
    int N, M, i;
    scanf("%d %d", &N, &M);
    if(M < N-1)
        printf("-1\n");
    else{
        ESet = (Edge)malloc(sizeof(struct EdgeNode) * M);
        for(i = 0; i < M; i++)
            scanf("%d %d %d", &ESet[i+1].V1, &ESet[i+1].V2, &ESet[i+1].weight);
        printf("%d\n", Krusral(N,M));
    }
    return 0;
}
