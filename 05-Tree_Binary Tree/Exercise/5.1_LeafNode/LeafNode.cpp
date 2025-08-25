#include "LeafNode.h"
#include <stdio.h>

int LeafNode(BiTree T){
    // 统计二叉树T中叶子节点的个数
    if(T == NULL)
        return 0;                          // 空树，返回0
    else if(T->lchild == NULL && T->rchild == NULL) 
        return 1;                          // 叶子结点，返回1
    else                                   // 递归
        return LeafNode(T->lchild) + LeafNode(T->rchild);
}