#include <stdlib.h>
#include <stdio.h>
#include<string.h>
typedef int WeightType;
typedef int DataType;
typedef int Vertex;
#define INFINITY 65535
#define  MaxVertexNum 201
#define NameNum 3
typedef char NameType[NameNum + 1];

/*图的结构体*/
typedef struct GNode *PtrToGNode;
struct GNode{
     int Nv; //顶点数
     int Ne;//边数
    WeightType Dist[MaxVertexNum][MaxVertexNum];//记录长度
    WeightType People[MaxVertexNum];//记录每个城市的救援队的数目
    int MinDist[MaxVertexNum];//最短距离
    int MaxPeople[MaxVertexNum];//最大的人数
    int Visited[MaxVertexNum];//访问标志
    int Pre[MaxVertexNum];//路径结点
    int Count[MaxVertexNum];//每个节点经过的城镇的数目
    int Country[MaxVertexNum];
    int KillPeople[MaxVertexNum];
};
typedef PtrToGNode MGraph;

int GetNum(char *Name, MGraph G, char S[][4]){
    int i;
    for(i = 0; i < G->Nv; i++){
        if(!strcmp(Name, S[i]))
            return i;
    }
}

void CreateMGraph(MGraph G, int VertexNum, int EdgeNum){
    Vertex L,C;
    G->Nv = VertexNum;
    G->Ne = EdgeNum;
    /*元素初始化*/
    for(L = 0; L < MaxVertexNum; L++){
        for(C = 0; C < MaxVertexNum; C++){
            G->Dist[L][C] = INFINITY;

        }
        G->Visited[L] = G->MaxPeople[L] = G->Pre[L] = G->People[L] = G->Count[L] = G->Country[L] = G->KillPeople[L] = 0;
        G->MinDist[L] = INFINITY;
    }
}

void BuildGraph(MGraph G, char S[][4], char *Start){
    int Team, Dist, i, num, C1, C2;
    NameType c1, c2;
    strcpy(S[0], Start);
    for(i = 1; i < G->Nv; i++){
        scanf("%s %d",&S[i], &G->People[i]);
    }
    for(i = 0; i < G->Ne; i++){
        scanf("%s %s %d", &c1, &c2, &Dist);
        C1 = GetNum(c1, G, S);
        C2 = GetNum(c2, G, S);
        G->Dist[C1][C2] = G->Dist[C2][C1] = Dist;
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
    G->MaxPeople[S] = G->People[S] = G->KillPeople[S];
    G->Pre[S] = -1;
    G->Count[S] = G->Country[S] = 1;
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
                    G->MaxPeople[j] = G->MaxPeople[minV] + G->People[j];
                    G->Country[j] = G->Country[minV] + 1;
                }
                else if(minDist + G->Dist[minV][j] == G->MinDist[j]){
                    G->Count[j] += G->Count[minV];

                    if(G->Country[j] < G->Country[minV] + 1){
                        G->Pre[j] = minV;
                        G->Country[j] = G->Country[minV] + 1;
                        G->MaxPeople[j] = G->MaxPeople[minV] + G->People[j];
                    }
                    else if((G->Country[j] == G->Country[minV] + 1) && (G->MaxPeople[minV] + G->People[j]> G->MaxPeople[j])){
                        G->Pre[j] = minV;
                        G->MaxPeople[j] = G->MaxPeople[minV] + G->People[j];    
                    }
                }
            }
        }
    }
}

void Output(MGraph G, int D, int S, char s[][4]){
    int Stack[MaxVertexNum];
    int i = D, j = 0;
    while(1){
        Stack[j] = G->Pre[i];
        if(G->Pre[G->Pre[i]] == -1)
            break;
        i = G->Pre[i];
        j++;
    }
    printf("%s", s[S]);
    for(i = j - 1; i >= 0; i--)
        printf("->%s", s[Stack[i]]);
    printf("->%s\n", s[D]);
    printf("%d %d %d\n", G->Count[D], G->MinDist[D], G->MaxPeople[D]);
}


int main(){
    MGraph G;
    char Name[MaxVertexNum][4];
    int N, M, s, d;
    NameType S, D;
    G = (MGraph)malloc(sizeof(struct GNode));
    scanf("%d %d %s %s", &N, &M, &S, &D);
    CreateMGraph(G, N, M);
    BuildGraph(G, Name, S);
    s = GetNum(S, G, Name);
    d = GetNum(D, G, Name);
    Dijkstra(G, s);
    Output(G, d, s, Name);
}