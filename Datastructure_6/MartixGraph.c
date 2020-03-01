#include <stdlib.h>
typedef struct GNode *PtrToGNode;
#include <stdio.h>
typedef int WeightType;
typedef int DataType;
typedef int Vertex;
#define INFINITY 65535
#define  MaxVertexNum 10
struct GNode{
     int Nv; //顶点数
     int Ne;//边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};

typedef PtrToGNode MGraph;



typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;//边的两个顶点 
    WeightType Weight;//边的权重
};
typedef PtrToENode Edge;

MGraph CreateMGaph(int VertexNum);
void InsertEdge(MGraph M, Edge E);
MGraph BuildGraph();


void InsertEdge(MGraph M, Edge E){
    M->G[E->V1][E->V2] = E->Weight;
    /*无向图要反向赋值*/
   M->G[E->V2][E->V1] = E->Weight;
}

MGraph CreateMGraph(int VertexNum){
    Vertex L,C;
    MGraph M;
    M = (MGraph)malloc(sizeof(struct GNode));
    M->Nv = VertexNum;
    M->Ne = 0;

    /*元素初始化*/
    for(L = 0; L < MaxVertexNum; L++)
        for(C = 0; C < MaxVertexNum; C++)
            M->G[L][C] = 0;

    return M;
}

MGraph BuildGraph(){
    MGraph M;
    Edge E;
    Vertex V;                                                                  
    scanf("%d",&V);
    M = CreateMGraph(V);
    scanf("%d", &(M->Ne));
    if(M->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < M->Ne; i++){
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            InsertEdge(M, E);
        }
    return M;
    }
    
}

int main(){
    printf("hello world");
}