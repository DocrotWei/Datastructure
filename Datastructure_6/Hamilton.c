#include <stdlib.h>
typedef struct GNode *PtrToGNode;
#include <stdio.h>
typedef int WeightType;
typedef int DataType;
typedef int Vertex;
#define INFINITY 65535
#define  MaxVertexNum 201

struct GNode{
     int Nv; //顶点数
     int Ne;//边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    int Visited[MaxVertexNum];
};
typedef PtrToGNode MGraph;

typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;//边的两个顶点 
    WeightType Weight;//边的权重
};
typedef PtrToENode Edge;

void InsertEdge(MGraph M, Edge E){
    M->G[E->V1][E->V2] = 1;
    /*无向图要反向赋值*/
   M->G[E->V2][E->V1] = 1;
}


void CreateMGraph(MGraph G, int EdgeNum, int VertexNum){
    Vertex L,C;
    G->Nv = VertexNum;
    G->Ne = EdgeNum;

    /*元素初始化*/
    for(L = 0; L < MaxVertexNum; L++){
        for(C = 0; C < MaxVertexNum; C++)
            G->G[L][C] = 0;
        G->Visited[L] = 0;
    }
}

void BuildGraph(MGraph G){
    Edge E;
    if(G->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < G->Ne; i++){
            scanf("%d %d", &E->V1, &E->V2);
            InsertEdge(G, E);
        }
    }
    
}


int main(){
    MGraph G;
    int M, N, K, v, Num, jug;
    Vertex FirstV, LastV, NextV;
    G = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d %d", &N, &M);
    CreateMGraph(G, M, N);
    BuildGraph(G);
    scanf("%d", &K);
    while(K--){//待验的k条回路
        jug = 1 ,FirstV = 0, LastV = 0;
        scanf("%d", &Num);
        if(Num != N + 1){
            jug = 0;
        }
        for(v = 0; v < Num; v++)
            G->Visited[v] = 0;
        for(v = 0; v < Num; v++){
            scanf("%d", &NextV);
            if(v == 0){
                FirstV = NextV;
            }
            else
            {
                if(!G->G[LastV][NextV])
                    jug = 0;
            }
            if(G->Visited[NextV]){
                if(v < Num - 1 || FirstV != NextV)
                    jug = 0;
            }
            G->Visited[NextV] = 1;
            LastV = NextV;
        }

        if(jug == 0)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}
