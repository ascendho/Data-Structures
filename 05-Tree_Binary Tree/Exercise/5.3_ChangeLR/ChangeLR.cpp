#include "ChangeLR.h"
#include <stdio.h>

void ChangeLR(BiTree T) {
    // 交换二叉树每个结点的左孩子和右孩子
    if(T == NULL) return;

    if(T->lchild == NULL && T->rchild == NULL) 
        return;                  // 左右子树均为空，返回
    else {                       // 交换左右子树
        BiTree temp = T->lchild; 
        T->lchild = T->rchild;
        T->rchild = temp;
    }

    ChangeLR(T->lchild);        // 递归交换左子树
    ChangeLR(T->rchild);        // 递归交换右子树
}