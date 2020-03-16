#include <stdlib.h>
#include <stdio.h>
typedef int WeightType;
typedef int DataType;
typedef int Vertex;
#define INFINITY 65535
#define  MaxVertexNum 505

/*图的结构体*/
typedef struct GNode *PtrToGNode;
struct GNode{
     int Nv; //顶点数
     int Ne;//边数
    WeightType Dist[MaxVertexNum][MaxVertexNum];//记录长度
    WeightType Team[MaxVertexNum];//记录每个城市的救援队的数目
    int MinDist[MaxVertexNum];//最短距离
    int MaxTeam[MaxVertexNum];//最大的人数
    int Visited[MaxVertexNum];//访问标志
    int Pre[MaxVertexNum];//路径结点
    int Count[MaxVertexNum];//每个节点最短路径数目
};
typedef PtrToGNode MGraph;


void CreateMGraph(MGraph G, int VertexNum, int EdgeNum){
    Vertex L,C;
    G->Nv = VertexNum;
    G->Ne = EdgeNum;
    /*元素初始化*/
    for(L = 0; L < MaxVertexNum; L++){
        for(C = 0; C < MaxVertexNum; C++){
            G->Dist[L][C] = INFINITY;

        }
        G->Visited[L] = G->MaxTeam[L] = G->Pre[L] = G->Team[L] = G->Count[L] = 0;
        G->MinDist[L] = INFINITY;
    }
}

void BuildGraph(MGraph G){
    int Team, C1, C2, RoadNum, i;
    for(i = 0; i < G->Nv; i++)
        scanf("%d", &G->Team[i]);

    for(i = 0; i < G->Ne; i++){
        scanf("%d %d %d", &C1, &C2, &RoadNum);
        G->Dist[C1][C2] = G->Dist[C2][C1] = RoadNum;
    }
}


void Dijkstra(MGraph G, Vertex S){
    int i, j;
    WeightType d, minV;
    WeightType minDist, minCost;
    for(i = 0; i < G->Nv; i++){
        G->MinDist[i] = G->Dist[S][i];
    }
    G->MinDist[S] = 0;
    G->MaxTeam[S] = G->Team[S];
    G->Pre[S] = -1;
    G->Count[S] = 1;
    for(i = 0; i < G->Nv; i++){
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
                    G->Pre[j] = minV;
                    G->Count[j] = G->Count[minV];
                    G->MaxTeam[j] = G->MaxTeam[minV] + G->Team[j];
                }
                else if((minDist + G->Dist[minV][j] == G->MinDist[j]) && (G->MaxTeam[j] < G->MaxTeam[minV] + G->Team[j])){
                    G->Pre[j] = minV;
                    G->Count[j] = G->Count[minV] + G->Count[j];
                    G->MaxTeam[j] = G->MaxTeam[minV] + G->Team[j];
                }
                else if(minDist + G->Dist[minV][j] == G->MinDist[j])
                    G->Count[j] = G->Count[minV] + G->Count[j];    
            }
        }
    }
}

void Output(MGraph G, int D, int S){
    int Stack[MaxVertexNum];
    int i = D, j = 0;

    printf("%d %d\n", G->Count[D], G->MaxTeam[D]);
    while(1){
        Stack[j] = G->Pre[i];
        if(G->Pre[G->Pre[i]] == -1)
            break;
        i = G->Pre[i];
        j++;
    }
    printf("%d", S);
    for(i = j - 1; i >= 0; i--)
        printf(" %d", Stack[i]);
    printf(" %d", D);
}

int main(){
    MGraph G;
    int N, M, S, D;
    G = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d %d %d %d", &N, &M, &S, &D);
    CreateMGraph(G, N, M);
    BuildGraph(G);
    Dijkstra(G, S);
    Output(G, D, S);
}