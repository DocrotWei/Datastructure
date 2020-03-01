#include<stdio.h>
#include<stdlib.h>
typedef int Datatype;
typedef int Vertex;
typedef int WeightType; 
#define MaxVertexNum 100
/*存放边得信息*/
typedef struct AdjNode *PtrToAdjNode;
struct AdjNode{
    Vertex V;
    WeightType Weight;
    PtrToAdjNode Next;
};
/*顶点数组的信息*/
typedef struct{
    PtrToAdjNode FirstEdge;
    Datatype Data;
} AdjList [MaxVertexNum];

/*邻接表整体信息*/
typedef struct GNode *PtrToGNode;
struct GNode{
    int Ne;//边数
    int Nv;//顶点数
    AdjList A;
};
typedef PtrToGNode LGragh;
/*输入边得信息*/
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

LGragh CreateLGraph(int VertexNum){
    LGragh L;
    Vertex V;
    L = (LGragh)malloc(sizeof(struct GNode));
    L->Ne = 0;
    L->Nv = VertexNum;
    for(V = 0; V < L->Nv; V++)
        L->A[V].FirstEdge = NULL;
    return L;
}

void InsertEdge(LGragh L, Edge E){
    PtrToAdjNode NewNode;
    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Weight = E->Weight;
    NewNode->V = E->V2;
    /*将V2插入V1表头的位置*/
    NewNode->Next = L->A[E->V1].FirstEdge;
    L->A[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Weight = E->Weight;
    NewNode->V = E->V1;
    /*将V2插入V1表头的位置*/
    NewNode->Next = L->A[E->V2].FirstEdge;
    L->A[E->V2].FirstEdge = NewNode;

}