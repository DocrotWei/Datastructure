#include <stdlib.h>
#include <stdio.h>
typedef int WeightType;
typedef int DataType;
typedef int Vertex;
#define INFINITY 65535
#define  MaxVertexNum 500

/*图的结构体*/
typedef struct GNode *PtrToGNode;
struct GNode{
     int Nv; //顶点数
     int Ne;//边数
    WeightType Dist[MaxVertexNum][MaxVertexNum];//记录长度
    WeightType Cost[MaxVertexNum][MaxVertexNum];//记录花费
    int MinDist[MaxVertexNum];
    int MinCost[MaxVertexNum];
    int Visited[MaxVertexNum];
};
typedef PtrToGNode MGraph;

typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;//边的两个顶点 
    WeightType Cost;//边的权重
    WeightType Dist;
};
typedef PtrToENode Edge;


void InsertEdge(MGraph M, Edge E){
    M->Dist[E->V1][E->V2] = E->Dist;
    /*无向图要反向赋值*/
   M->Dist[E->V2][E->V1] = E->Dist;

   M->Cost[E->V1][E->V2] = E->Cost;
    /*无向图要反向赋值*/
   M->Cost[E->V2][E->V1] = E->Cost;
}

void CreateMGraph(MGraph G, int VertexNum, int EdgeNum){
    Vertex L,C;
    G->Nv = VertexNum;
    G->Ne = EdgeNum;
    /*元素初始化*/
    for(L = 0; L < MaxVertexNum; L++){
        for(C = 0; C < MaxVertexNum; C++){
            G->Dist[L][C] = INFINITY;
            G->Cost[L][C] = INFINITY;
        }
        G->Visited[L] = 0;
        G->MinCost[L] = G->MinDist[L] = INFINITY;
    }
}

void BuildGraph(MGraph G){
    Edge E;
    if(G->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < G->Ne; i++){
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->Dist, &E->Cost);
            InsertEdge(G, E);
        }
        free(E);
    }   
}


void Dijkstra(MGraph G, Vertex S){
    int i, j;
    WeightType d, minV;
    WeightType minDist, minCost;
    for(i = 0; i < G->Nv; i++){
        G->MinDist[i] = G->Dist[S][i];
        G->MinCost[i] = G->Cost[S][i];
    }
    G->MinDist[S] = 0;
    G->MinCost[S] = 0;
    G->Visited[S] = 1;
    for(i = 1; i < G->Nv; i++){
        minDist = INFINITY;
        /*找连通的最小值*/
        for(j = 0; j < G->Nv; j++){
            if(!G->Visited[j]){
                if(G->MinDist[j] <= minDist){
                    minV = j;
                    minDist = G->MinDist[minV];
                }
            }
        }
        if(minDist < INFINITY)
            G->Visited[minV] = 1;
        else
            break;
        /*对未访问过的路径更新最短路*/
        for(j = 0; j < G->Nv; j++){
            if(!G->Visited[j]){
                if((minDist + G->Dist[minV][j]) < G->MinDist[j]){
                    G->MinDist[j] = minDist + G->Dist[minV][j];
                    G->MinCost[j] = G->MinCost[minV] + G->Cost[minV][j];
                }
                else if((minDist + G->Dist[minV][j] == G->MinDist[j]) && (G->MinCost[j] > G->MinCost[minV] + G->Cost[minV][j])){
                    G->MinCost[j] = G->MinCost[minV] + G->Cost[minV][j];
                }
            }
        }
    }

}
int main(){
    MGraph G;
    int N, M, S, D;
    G = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d %d %d %d", &N, &M, &S, &D);
    CreateMGraph(G, N, M);
    BuildGraph(G);
    Dijkstra(G, S);
    printf("%d %d", G->MinDist[D], G->MinCost[D]);
}