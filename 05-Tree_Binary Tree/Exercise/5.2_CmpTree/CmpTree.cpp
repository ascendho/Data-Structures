#include "CmpTree.h"
#include <stdio.h>

int CmpTree(BiTree T1, BiTree T2) {
    // 判断两棵二叉树是否相等
    if (T1 == NULL && T2 == NULL)
        return 1;                       // 都是NULL，相等
    else if (T1 == NULL || T2 == NULL)
        return 0;                       // 只有一个为NULL，不等
    if(T1->data!=T2->data)
        return 0;                       // 根节点不相等，直接返回不等，否则递归

    int left=0, right=0;
    left=CmpTree(T1->lchild, T2->lchild);
    right=CmpTree(T1->rchild, T2->rchild);
    return left && right;
}
