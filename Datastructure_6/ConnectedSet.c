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
    int Visited;
} AdjList [MaxVertexNum];

/*邻接表整体信息*/
typedef struct GNode *PtrToGNode;
struct GNode{
    int Ne;//边数
    int Nv;//顶点数
    AdjList A;
};
typedef PtrToGNode LGraph;
/*输入边得信息*/
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

void CreateLGraph(LGraph G, int VertexNum, int EdgeNum){
    Vertex V;
    G->Ne = EdgeNum;
    G->Nv = VertexNum;
    for(V = 0; V < G->Nv; V++){
        G->A[V].FirstEdge = NULL;
        G->A[V].Visited = 0;
    }
}

void InsertEdge(LGraph G, Edge E){
    PtrToAdjNode NewNode, P, Q;
    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Weight = 1;
    NewNode->V = E->V2;
    if(G->A[E->V1].FirstEdge == NULL || G->A[E->V1].FirstEdge->V > E->V2){
        /*将V2插入V1表头的位置*/
        NewNode->Next = G->A[E->V1].FirstEdge;
        G->A[E->V1].FirstEdge = NewNode;
    }
    else{
        P = G->A[E->V1].FirstEdge;
        Q = P->Next;
        while(Q && Q->V < E->V2){
            P = Q;
            Q = Q->Next;
        }
        NewNode->Next = Q;
        P->Next = NewNode;
    }

    NewNode = (PtrToAdjNode)malloc(sizeof(struct AdjNode));
    NewNode->Weight = 1;
    NewNode->V = E->V1;
    if(G->A[E->V2].FirstEdge == NULL || G->A[E->V2].FirstEdge->V > E->V1){
        /*将V2插入V1表头的位置*/
        NewNode->Next = G->A[E->V2].FirstEdge;
        G->A[E->V2].FirstEdge = NewNode;
    }
    else{
        P = G->A[E->V2].FirstEdge;
        Q = P->Next;
        while(Q && Q->V < E->V1){
            P = Q;
            Q = Q->Next;
        }
        NewNode->Next = Q;
        P->Next = NewNode;
    }
}

void BuildGraph(LGraph G){
    Vertex V;
    Edge E;
    E = (Edge)malloc(sizeof(struct ENode));
    for(V = 0; V < G->Ne; V++){
        scanf("%d %d", &(E->V1), &(E->V2));
        InsertEdge(G, E);
    }
    free(E);
}
void Visit(Vertex V){
    printf("%d ", V);
}

void BFS(LGraph G, Vertex S, void (*Visit)(Vertex) ){
    int Queue[11], j = 0, r = 0;
    Vertex U, V;
    PtrToAdjNode W;
    Queue[j++] = S;
    G->A[S].Visited = 1;
    Visit(S);
    while(j != r){//队列不为空
        V = Queue[r++];
        
        for(W = G->A[V].FirstEdge; W; W = W->Next){
            if(!G->A[W->V].Visited){
                G->A[W->V].Visited = 1;
                Queue[j++] = W->V;
                Visit(W->V);
            }
        }
    }
};

void DFS(LGraph G, Vertex V, void(*Visit)(Vertex)){
    PtrToAdjNode W;
    G->A[V].Visited = 1;
    Visit(V);
    for(W = G->A[V].FirstEdge; W; W = W->Next){
        if(!G->A[W->V].Visited)
            DFS(G, W->V, Visit);
    }
}

int main(){
    LGraph G;
    int N, M, i;
    G = (LGraph)malloc(sizeof(struct GNode));
    scanf("%d %d", &N, &M);
    CreateLGraph(G, N, M);
    BuildGraph(G);
    for(i = 0; i < G->Nv; i++){   
        if(!G->A[i].Visited){
            printf("{ ");
            DFS(G, i, Visit);
            printf("}\n");
        }
        
    }
    for(i = 0; i < G->Nv; i++){
        G->A[i].Visited = 0;
    }
    for(i = 0; i < G->Nv; i++){   
        if(!G->A[i].Visited){
            printf("{ ");
            BFS(G, i, Visit);
            printf("}\n");
        }
        
    } 
}