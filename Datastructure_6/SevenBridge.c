#include <stdlib.h>
#include <stdio.h>
typedef int WeightType;
typedef int DataType;
typedef int Vertex;
#define INFINITY 65535
#define  MaxVertexNum 1000
/*树的结构*/
typedef struct GNode *PtrToGNode;
struct GNode{
     int Nv; //顶点数
     int Ne;//边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    int Visited[MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateMGaph(int VertexNum);
MGraph BuildGraph();

MGraph CreateMGraph(MGraph G, int VertexNum){
    Vertex L,C;

    G->Nv = VertexNum;
    G->Ne = 0;
    /*元素初始化*/
    for(L = 0; L < MaxVertexNum; L++)
        for(C = 0; C < MaxVertexNum; C++)
            G->G[L][C] = 0;
        G->Visited[L] = 0;
    return G;
}

MGraph BuildGraph(MGraph G, int EdgeNum, int VertaxNum){
    Vertex V1, V2;                                                               
    G = CreateMGraph(G, VertaxNum);
    G->Ne = EdgeNum;
    if(G->Ne!= 0){
        for (int i = 0; i < G->Ne; i++){
            scanf("%d %d", &V1, &V2);
            G->G[V1-1][V2-1] = 1;
            G->G[V2-1][V1-1] = 1;
        }
    return G;
    }
}

void DFS(MGraph G, int V){
    int i;
    G->Visited[V] = 1;
    for(i = 0; i < G->Nv; i++)
        if(G->G[V][i] && !G->Visited[i])
            DFS(G, i);
}

int CheckGraph(MGraph G){
    int i,j,A;
    for(i = 0; i < G->Nv; i++){
        A = 0;
        for(j = 0; j < G->Ne; j++)
            A += G->G[i][j];
        if(A % 2)
            return 0; //度不为偶数
    }
    return 1;//度为偶数
}

int main(){
    int Edge, Vertex, i;
    MGraph G;
    G = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d %d", &Vertex, &Edge);
    BuildGraph(G, Edge, Vertex);
    DFS(G, 0);
    for(i = 0; i < G->Nv; i++){
        if(!G->Visited[i])
            break;  
    }
    if(i < G->Nv)
        printf("0\n");
    else
        printf("%d\n", CheckGraph(G));

    return 0;
}