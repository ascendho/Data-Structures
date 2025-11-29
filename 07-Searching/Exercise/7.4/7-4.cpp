#include<iostream>
using namespace std;
typedef struct BiTNode
{
	int data;
	int count;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void SearchBST(BiTree &T,int X)
{
	BiTree s=new BiTNode;		//生成一个数据域为X的新结点s
	s->data=X;
	s->count=0;
	s->lchild=s->rchild=NULL;
	if(!T)						//如果该树为空则结束该函数
	{
		T=s;
		s->count++;
		return;
	}   
	BiTree q=T,f=NULL;
	while(q)
	{
		if(q->data==X)
		{						//如果找到该值则计数加1
			q->count++;
			return ;
		}  
		f=q;
		if(X<q->data)			//X小于当前结点值，使指针指向左子树
			q=q->lchild;
		else					//X大于当前结点值，使指针指向右子树
			q=q->rchild;
	}
	if(f->data>X)
	{							//如果找不到，就将新结点插入树中
		f->lchild=s;
		s->count++;
	}
	else
	{
		f->rchild=s;
		s->count++;
	}
}
void PrintData(BiTree T)
{//中序遍历输出二叉树T
    if(T==NULL) return;
    else
    {
        PrintData(T->lchild);
        cout<<T->data<<" ";
        PrintData(T->rchild);
    }
}
void PrintCount(BiTree T)
{//中序遍历输出二叉树T计数
    if(T==NULL) return;
    else
    {
        PrintCount(T->lchild);
        cout<<T->count<<" ";
        PrintCount(T->rchild);
    }
}
int main()
{
	int n;
	cin>>n;
	int e;        			//变量e用于接收输入数据
  	BiTree T=NULL;
	for(int i=0;i<n;i++)
	{//基于非递归的二叉排序树的结点的查找和插入
		cin>>e;
		SearchBST(T,e);
	}
	PrintData(T);			//中序遍历输出二叉树T结点
	cout<<endl;
	PrintCount(T);   		//中序遍历输出二叉树T计数
	cout<<endl;
	return 0;
}
