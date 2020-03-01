#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define Max 100
/*代表每个鳄鱼*/
typedef struct CNode{
    double X;
    double Y;
    int Visited;
}Crocodile[Max];

typedef struct GNode *PtrToGNode;
struct GNode{  
    double D;     /* 距离 */
    int N;     /* 鳄鱼数   */
    Crocodile C;  /* 邻接表 */
};
typedef PtrToGNode Graph; /* 以邻接表方式存储的图类型 */

void InitializeGrqph(Graph G){
    int i;
    for(i = 0; i < G->N; i++){
        G->C[i].X = G->C[i].Y = G->C[i].Visited = 0;
    }
}

void BuildGraph(Graph G){
    int i;
    for(i = 0; i < G->N; i++){
        scanf("%lf %lf", &G->C[i].X, &G->C[i].Y);
    }
}

int FirstJump(Graph G, int V){
    if(sqrt(G->C[V].X * G->C[V].X + G->C[V].Y * G->C[V].Y) <= (G->D + 7.5))
        return 1;
    else
        return 0;
}

int Jump(Graph G, int V, int W){
    double x;
    double y;
    x = G->C[V].X - G->C[W].X;
    x = x * x;
    y = G->C[V].Y - G->C[W].Y;
    y = y * y;
    if(sqrt(y + x) <= G->D)
        return 1;
    else
        return 0;  
}
int IsSafe(Graph G, int V){
    if(((G->C[V].X + G->D) >= 50) || ((G->C[V].X - G->D) <= -50))
        return 1;
    if(((G->C[V].Y + G->D) >= 50) || ((G->C[V].Y - G->D) <= -50))
        return 1;
    return 0;
}

int DFS(Graph G, int V){
    int Answer, v;
    G->C[V].Visited = 1;
    if( IsSafe(G, V))
        Answer = 1;
    else{
        for(v = 0; v < G->N; v++){
            if(!G->C[v].Visited && Jump(G, v, V)){
                Answer = DFS(G, v);
                if(Answer == 1)
                    break;
            }
        }
    }
     return Answer;   
}

void Save007(Graph G){
    int Answer;
    if(G->N == 0){
        Answer = 0;
    }
    for(int i = 0; i < G->N; i++){
        if(!G->C[i].Visited && FirstJump(G, i)){
            if(G->D >= 42.5){
                Answer = 1;
                break;
            }
            else{
                Answer = DFS(G, i);
                if(Answer == 1)
                    break;
            }
        }
    }
    if(Answer == 1)
        printf("Yes");
    else 
        printf("No");
}
int main(){
    int N, Dist;
    Graph G;
    G = (Graph)malloc(sizeof(struct GNode));
    scanf("%d %lf", &G->N, &G->D);
    InitializeGrqph(G);
    BuildGraph(G);
    Save007(G);
}