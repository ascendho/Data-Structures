#include "AllPath.h"
#include <stdio.h>
#include <iostream>

using namespace std;

char path[100];

void AllPath(BiTree T, char path[], int pathlen) {
    // 将每一条从叶到根的路径打印出来，pathlen初始为0
    if (T != NULL) {
        if (T->lchild == NULL && T->rchild == NULL) {    // 叶子节点
            path[pathlen] = T->data;
            for (int i = pathlen; i >= 0; i--) {
                cout << path[i];
            }
            cout << endl;
        } else {
            path[pathlen] = T->data;                // 记录当前节点的值
            pathlen++;                              // 路径长度加1
            AllPath(T->lchild, path, pathlen);      // 递归遍历左子树
            AllPath(T->rchild, path, pathlen);      // 递归遍历右子树
            pathlen--;                              // 恢复环境
        }
    }
}