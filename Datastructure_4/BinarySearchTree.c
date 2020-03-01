#include<stdlib.h>
#include <stdio.h>
typedef struct TreeNode *BinTree;
#define ElementType int
typedef BinTree Position;
struct TreeNode
{
    ElementType Data;
    BinTree Right;
    BinTree Left;
};

/*查找函数
    输入变量：
    item 查找的元素
    Bst 二叉查找树
    输出变量;
    返回相应的结点地址
*/
Position Find(ElementType item, BinTree BST){
    if(!BST)
        return NULL;
    else if(item > BST->Data)
        return Find(item, BST->Right);
    else if(item < BST->Data)
        return Find(item, BST->Left);
    else
        return BST;
}

/*改善尾递归，直接利用循环即可实现*/
Position IterFind(ElementType X, BinTree BST){
    while(BST){//保证该结点一直存在
        if(X > BST->Data)
            BST = BST->Right;
        else if(X < BST->Data)
            BST = BST->Left;
        else
            return BST;
    }
    return NULL;
}

Position FindMin(BinTree BST){
    if(!BST)
        while(BST->Left){
            BST = BST->Left;
        }
    return BST;
}

Position FindMax(BinTree BST){
    if(!BST)
        return NULL;
    else if(!BST->Right)
        return BST;
    else return FindMax(BST->Right);
}

BinTree Insert(ElementType InsertEle, BinTree BST){
    if(!BST){//找到空结点进行插入
        BST = (BinTree)malloc(sizeof(struct TreeNode));
        BST->Data = InsertEle;
        BST->Left = BST->Right = NULL;
    }
    else{
        if(InsertEle > BST->Data)
            BST = Insert(InsertEle, BST->Right);
        else if(InsertEle < BST->Data)
            BST = Insert(InsertEle, BST->Left);
    }
    //如果存在的化就什么也不做
    return BST;

}

BinTree Delete(ElementType DeleteEle, BinTree BST){
    Position Tmp;//用来释放空间
    if(!BST)
        printf("未找到删除的元素");
    else if(DeleteEle > BST->Right)
        BST->Right = Delete(DeleteEle, BST->Right);
    else if(DeleteEle < BST->Left)
        BST->Left = Delete(DeleteEle, BST->Left);
    else{//找着该元素
        if(BST->Left && BST->Right){
            Tmp = FindMin(BST->Right);
            BST->Data = Tmp->Data;
            BST->Right = Delete(Tmp->Data, BST->Right);
        }
        else{
            Tmp = BST;
            if(!BST->Left)
                BST = BST->Right;
            else if(!BST->Right)
                BST = BST->Left;
            free(Tmp);
        }

        return BST;
    }
}