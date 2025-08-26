#include "DoubleTraverse.h"
#include <iostream>
using namespace std;

void DoubleTraverse(BiTree T) {
    if(T){
        cout << T->data;            // 访问根结点
        DoubleTraverse(T->lchild);  // 双序遍历左子树
        cout << T->data;            // 访问根结点
        DoubleTraverse(T->rchild);  // 双序遍历右子树
    }

}
