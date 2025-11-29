#include<iostream>
using namespace std;
typedef struct BSTNode
{//二叉排序树的二叉链表存储表示
	int data;
	struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;
void InsertBST(BSTree &T,int e){
	if(!T)
	{                            		//找到插入位置，递归结束
		BSTree S=new BSTNode;    		//生产新结点*S
		S->data=e;               		//新结点*S的数据域置为e
		S->lchild=NULL;          		//把新结点作为叶子结点
		S->rchild=NULL;
		T=S;                     		//把新结点*S链接到已找到的插入位置
	}
	else
	{
		if(e<T->data)
			InsertBST(T->lchild,e);      //将*S插入左子树
		else
			InsertBST(T->rchild,e);      //将*S插入右子树
	}
}
void Print(BSTree T)
{//中序输出以T为根的二叉排序树的所有结点
	if(T)
	{
		Print(T->lchild);
		cout<<T->data<<" ";
		Print(T->rchild);
	}   	
}
void PrintAllx(BSTree T,int x)
{//在二叉排序树T中，查找值≥x的结点并输出
	BSTree p=T;
	if(p)
	{
		while(p&&p->data<x)					//沿右分枝向下，找到第一个值≥x的结点
		p=p->rchild;
		T=p;								//T所指结点是值≥x的结点的树的根
		if(p)								//找到第一个值<x的结点
		{
			BSTree f=p;
			p=p->lchild;
			while(p&&p->data>=x)			//沿左分枝向下，找到第一个值<x的结点
			{
				f=p;						//f是p的双亲结点的指针，且指向第一个值≥x的结点
				p=p->lchild;
			}
			if(p) f->lchild=NULL;			//双亲与找到的第一个值<x的结点断开
			Print(T);						//输出以T为根的子树
		}									//内层if(p)
	}										//外层if(p)
}
int main()
{
	BSTree T=NULL;
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		int e;
		cin>>e;
		InsertBST(T,e);
	}
	Print(T);
	cout<<endl;
	int x;
	cin>>x;
	PrintAllx(T,x);
}
