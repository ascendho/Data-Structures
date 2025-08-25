// 二叉链表定义
typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

int CmpTree(BiTree T1, BiTree T2);