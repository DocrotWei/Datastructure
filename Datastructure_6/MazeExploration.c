#include<stdio.h>
#include<stdlib.h>
#define ElementType int
#define Maxsize 1000
#define ERROR -1
/********************************堆部分****************************************/
/*堆结点：Top堆顶位置 Data堆栈数组*/
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data[Maxsize];
    int Top;
};
/*初始化数组*/
void InitialiseS(Stack S){
    S->Top = -1;
}
/*入栈：item 需要入栈的元素 Stack 入栈的堆*/
void Push(ElementType item, Stack PtrS){
   if(PtrS->Top == Maxsize-1){ //首先应该判断堆栈是否已经满了
       printf("堆栈满");
       return;
   }
   else{ //首先栈顶升高，把元素压入栈中
       PtrS->Data[++(PtrS->Top)] = item;
       return;
   }
}
/*出栈： PtrS堆栈 返回值：出栈的元素*/
ElementType Pop(Stack PtrS){
    if (PtrS->Top == -1){
        printf("堆栈空");
        return ERROR;
    }
    else
        return PtrS->Data[(PtrS->Top)--];//把元素弹出后，在降低栈顶，注意与压栈的区别
}
/*返回顶层元素：PtrS 返回值：返回顶层元素*/
ElementType Top(Stack PtrS){
    if(PtrS->Top == -1){
        printf("堆栈空");
        return ERROR;
    }
    else
        return PtrS->Data[PtrS->Top];
}
/*判断堆栈是否为空 返回值：1为空*/
int IsEmpty(Stack S){
    return S->Top < 0;
}

/***************************邻接表位置*****************************/
typedef int Datatype;
typedef int Vertex;
typedef int WeightType; 
#define MaxVertexNum 1000

/*边节点: V：对应的顶点 Weight：边得比重 Next：下一条边的位置*/
typedef struct EdgeNode *PtrToEdgeNode;
struct EdgeNode{
    Vertex V;
    WeightType Weight;
    PtrToEdgeNode Next;
};

/*顶点结点： FirstEdge:第一条边得位置 Data：顶点的数据类型*/
typedef struct{
    PtrToEdgeNode FirstEdge;
    char Visited;
} AdjList [MaxVertexNum];

/*邻接表整体信息：Ne：边数数，Nv：顶点数 A：顶点表的表头*/
typedef struct GNode *PtrToGNode;
struct GNode{
    int Ne;//边数
    int Nv;//顶点数
    AdjList A;
};
typedef PtrToGNode LGragh;

/*边得输入信息： V1：输入结点 ，V2：输出结点，weight：两条边得权重*/
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

/*初始化图*/
LGragh CreateLGraph(LGragh G, int VertexNum){
    int V;
    G->Ne = 0;
    G->Nv = VertexNum;
    for(V = 0; V < G->Nv; V++){
        G->A[V].FirstEdge = NULL;
        G->A[V].Visited = 0;
    }
    return G;
}
/*把边插入到图中: L:插入的图， E：边结点方便操作*/
void InsertEdge(LGragh L, Edge E){
    PtrToEdgeNode NewNode, p, q;
    NewNode = (PtrToEdgeNode)malloc(sizeof(struct EdgeNode));
    NewNode->Weight = 1;
    NewNode->V = (E->V2-1);
    /*将V2插入V1表头的位置*/
    if(L->A[E->V1-1].FirstEdge == NULL || L->A[E->V1-1].FirstEdge->V > E->V2-1){
        NewNode->Next = L->A[E->V1-1].FirstEdge;
        L->A[E->V1-1].FirstEdge = NewNode;
    }
    else{
        p = L->A[E->V1-1].FirstEdge;
        q = p->Next;
        while(q && q->V < (E->V2-1)){
            p = q;
            q = q->Next;
        }
        NewNode->Next = q;
        p->Next = NewNode;
    }

    NewNode = (PtrToEdgeNode)malloc(sizeof(struct EdgeNode));
    NewNode->Weight = 1;
    NewNode->V = (E->V1-1);
    /*将V2插入V1表头的位置*/
    if(L->A[E->V2-1].FirstEdge == NULL || L->A[E->V2-1].FirstEdge->V > E->V1-1){
        NewNode->Next = L->A[E->V2-1].FirstEdge;
        L->A[E->V2-1].FirstEdge = NewNode;
    }
    else{
        p = L->A[E->V2-1].FirstEdge;
        q = p->Next;
        while(q && q->V < (E->V1-1)){
            p = q;
            q = q->Next;
        }
        NewNode->Next = q;
        p->Next = NewNode;
    }
}

LGragh BuildGraph(LGragh G, Vertex VNum, int ENum){
    int i;
    Edge E;
    G = CreateLGraph(G, VNum);
    G->Ne = ENum;
    E = (Edge)malloc(sizeof(struct ENode));
    for(i =0; i < G->Ne; i++){
        scanf("%d %d", &(E->V1), &(E->V2));
        InsertEdge(G, E);
    }
    free(E);
    return G;
}

void CheckGraph(LGragh G){
    int i;
    for(i = 0; i < G->Nv; i++)
        if(!G->A[i].Visited)
            break;
    if(i < G->Nv)
        printf(" 0\n");
    else
        printf("\n");
}

void DFS(LGragh G, int FirstPoint){
    PtrToEdgeNode edge;
    Stack S = (Stack)malloc(sizeof(struct SNode));
    InitialiseS(S);
    G->A[FirstPoint].Visited = 1;
    printf("%d", FirstPoint + 1);
    Push(FirstPoint, S);
    while(!IsEmpty(S)){
        FirstPoint = Top(S);
        for(edge = G->A[FirstPoint].FirstEdge; edge; edge = edge->Next){
            if(!G->A[edge->V].Visited){
                G->A[edge->V].Visited = 1;
                printf(" %d", edge->V + 1);
                Push(edge->V, S);
                break;
            }
        }
        if(!edge){
            FirstPoint = Pop(S);
            if(!IsEmpty(S))
                printf(" %d", Top(S) + 1);
        }
    }
}
int main(){
    Vertex V;
    int E, F;
    LGragh G;
    G = (LGragh)malloc(sizeof(struct GNode));
    scanf("%d %d %d", &V, &E, &F);
    G = BuildGraph(G, V, E);
    DFS(G, F - 1);
    CheckGraph(G);
    return 0;
}