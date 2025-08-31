// 二叉链表定义
typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void AllPath(BiTree T,char path[],int pathlen);