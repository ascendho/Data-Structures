#include "LongestPath.h"
#include <iostream>

using namespace std;

void LongestPath(BiTree T) {
    // 寻找二叉树中的一条最长路径
    BiTree p = T, l[MAXSIZE], s[MAXSIZE];  // l,s是栈的元素指针数组，l数组存储当前最长路径上的节点
    int top = 0, longest = 0;
    int tag[MAXSIZE];  // tag是标记数组，元素为1表示当前节点已被访问，0表示未被访问
    
    while (p || top > 0) {
        // 遍历左子树
        while (p) {
            s[++top] = p;
            tag[top] = 0;
            p = p->lchild;
        }
        
        if (tag[top] == 1) {  // 当前节点为右子树的根
            // 只有一个叶子节点时才查看路径长度
            if (!s[top]->lchild && !s[top]->rchild) {
                if (top > longest) {  // 更新最长路径
                    for (int i = 1; i <= top; i++) {
                        l[i] = s[i];
                    }
                    longest = top;
                }
            }
            top--;  // 将栈顶指针减1
        } else if (top > 0) {  // 当前节点为左子树的根
            tag[top] = 1;
            p = s[top]->rchild;
        }
    }
    
    // 输出结果
    cout << longest << endl;
    for (int k = 1; k <= longest; k++) {
        cout << l[k]->data;
    }
    cout << endl;
}