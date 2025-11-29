#include<iostream>
#include <string.h>
using namespace std;

typedef struct BiTNode
{
   char data; 
   struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void CreateBiTree(BiTree &T,char a[],int &i)
{//先序建立二叉树
	if(a[i]=='#') T=NULL;
	else
	{
		T=new BiTNode;
		T->data=a[i];
		CreateBiTree(T->lchild,a,++i);
		CreateBiTree(T->rchild,a,++i);
	}
}
BiTree pre=NULL;									//前驱指针
void JudgeBST(BiTree T,int &flag)
{//判断二叉树T是否是二叉排序树，flag初值为1
	if(T!=NULL&&flag)
	{ 
		JudgeBST(T->lchild,flag);					//中序遍历左子树
		if(pre==NULL) pre=T;						//中序遍历的第一个结点不必判断
		else if(pre->data<T->data) pre=T;			//前驱指针指向当前结点
		else flag=0;								//不是二叉排序树
		JudgeBST(T->rchild,flag);					//中序遍历右子树
}
}
int main()
{
	char a[99];
	//输入先序序列
	cin>>a;
	if(strcmp(a,"#")!=0){
		int i=-1;
		int flag=1;
		BiTree T;
		CreateBiTree(T,a,++i);
		JudgeBST(T,flag);
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
