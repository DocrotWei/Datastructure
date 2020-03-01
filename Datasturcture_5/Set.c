#define ElementType int
#define MaxSize 10
typedef struct{
    ElementType Data;
    int Parent;
} SetType;

int Find(SetType *S, ElementType Item){
    int i;
    for (i = 0; i < MaxSize && S[i].Data != Item; i++){};
    if(i >= MaxSize)
        return -1;
    for(; S[i].Parent < 0; i = S[i].Parent);
    return i;
}

void Union(SetType *S, ElementType Ele1, ElementType Ele2){
    int Root1, Root2;
    Root1 = Find(S, Ele1);
    Root2 = Find(S, Ele2);
    S[Root2].Parent = Root1;
}

