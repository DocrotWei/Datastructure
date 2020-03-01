//tongbuceshi
#include <stdlib.h>
typedef struct GNode *PtrToGNode;
#include <stdio.h>
typedef int WeightType;
typedef int Vertex;
#define INFINITY 65535
#define  MaxVertexNum 100
struct GNode{
     int Nv; //顶点数
     int Ne;//边数
    WeightType Animal[MaxVertexNum][MaxVertexNum];
    WeightType Dist[MaxVertexNum][MaxVertexNum];//记录最小长度
};
typedef PtrToGNode MGraph;

typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;//边的两个顶点 
    WeightType Weight;//边的权重
};
typedef PtrToENode Edge;


void InsertEdge(MGraph G, Edge E){
    G->Animal[E->V1][E->V2] = E->Weight;
    /*无向图要反向赋值*/
   G->Animal[E->V2][E->V1] = E->Weight;
}

void CreateMGraph(MGraph G, int VertexNum, int EdgeNum){
    Vertex L, C;
    G->Nv = VertexNum;
    G->Ne = EdgeNum;
    /*元素初始化*/
    for(L = 0; L < MaxVertexNum; L++)
        for(C = 0; C < MaxVertexNum; C++){
            G->Animal[L][C] = INFINITY;
            G->Dist[L][C] = 0;
        }
}

void BuildGraph(MGraph G){
    Edge E;
    if(G->Ne != 0){
        E = (Edge)malloc(sizeof(struct ENode));
        for (int i = 0; i < G->Ne; i++){
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            E->V1--;
            E->V2--;
            InsertEdge(G, E);
        }
    }
    
}

void Floyd(MGraph G){
    int i, j, k;
    for(i = 0; i < G->Nv; i++)
        for(j = 0; j < G->Nv; j++)
            G->Dist[i][j] = G->Animal[i][j];
    for(k = 0; k < G->Nv; k++)
        for(i = 0; i < G->Nv; i++)
            for(j = 0; j < G->Nv; j++)
                if((G->Dist[i][k] + G->Dist[k][j]) < G->Dist[i][j])
                    G->Dist[i][j] = G->Dist[i][k] + G->Dist[k][j];
}

WeightType FindMaxAnimal(MGraph G, Vertex V){
    Vertex v;
    WeightType Max = 0;
    for(v = 0; v < G->Nv; v++){
        if(G->Dist[V][v] > Max && (V != v))
            Max = G->Dist[V][v];
    }
    return Max;
}
void FindAnimal(MGraph G){
    int i, minV;
    WeightType MaxDist, MinAnimal;
    Floyd(G);
    MinAnimal = INFINITY;
    if(G->Nv <= 1){
        printf("0\n");
        return;
    }
    for(i = 0; i < G->Nv; i++){
        MaxDist = FindMaxAnimal(G, i);
        if(MaxDist == INFINITY){
            printf("0\n");
            return;
        }
        if(MaxDist < MinAnimal){
            MinAnimal = MaxDist;
            minV = i + 1;
        }
    }
    printf("%d %d\n", minV, MinAnimal);
}

int main(){
    MGraph G;
    int VertexNum, EdgeNum;
    G = (MGraph)malloc(sizeof (struct GNode));
    scanf("%d %d", &VertexNum, &EdgeNum);
    CreateMGraph(G, VertexNum, EdgeNum);
    BuildGraph(G);
    FindAnimal(G);
}
//jiushi1dhlashdlasda
