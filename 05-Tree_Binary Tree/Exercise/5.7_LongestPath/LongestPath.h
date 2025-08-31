// 二叉链表定义
typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

#define MAXSIZE 100

void LongestPath(BiTree T);