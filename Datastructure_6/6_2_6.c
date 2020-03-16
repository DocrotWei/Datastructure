#include<stdio.h>
#include<stdlib.h>
#define MaxSize 105
typedef int WeightType;
struct GNode{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxSize][MaxSize]; /* 邻接矩阵 */
    int Indegree[MaxSize];
    int Earlist[MaxSize];
};
typedef struct GNode *PtrToGNode;
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

MGraph CreateGraph(int Nv, int Ne){
    int i, j;
    MGraph G;
    G = (MGraph)malloc(sizeof(struct GNode));
    G->Nv = Nv;
    G->Ne = Ne;
    for(i = 0; i < Nv; i++){
        for(j = 0; j < Nv; j++)
            G->G[i][j] = -1;
        G->Indegree[i] = 0;
        G->Earlist[i] = 0;
    }
    return G;
}

void BuildGraph(MGraph G){
    int i, V1, V2, Time;
    for(i = 0; i < G->Ne; i++){
        scanf("%d %d %d", &V1, &V2, &Time);
        G->G[V1][V2] = Time;
        G->Indegree[V2]++;
    }
}

int TopSort(MGraph G){
    int i, j, k, cnt;
    for(i = 0; i < G->Nv; i++){
        for(j = 0; j < G->Nv; j++)
            if(G->Indegree[j] == 0){
                G->Indegree[j] = -1;
                break;
            }
        if(j == G->Nv)
            return 0;
        for(k = 0; k < G->Nv; k++){
            if(G->Indegree[k] != -1 && G->G[j][k] >= 0){
                G->Indegree[k]--;
                if(G->Earlist[k] < G->Earlist[j] + G->G[j][k])
                    G->Earlist[k] = G->Earlist[j] + G->G[j][k];
            }
        }
    }
    return 1;
}

void Output(int N, MGraph G){
    int i, Maxitem = 0;
    if(N == 0)
        printf("Impossible");
    else{
        for(i = 0; i < G->Nv; i++)
            if(Maxitem < G->Earlist[i])
                Maxitem = G->Earlist[i];
        printf("%d", Maxitem);
    }
}
int main(){
    MGraph G;
    int N, M;
    scanf("%d %d", &N, &M);
    G = CreateGraph(N, M);
    BuildGraph(G);
    N = TopSort(G);
    Output(N,G);
}