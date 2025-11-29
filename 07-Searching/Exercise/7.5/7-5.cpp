#include<iostream>
#include <string.h>
using namespace std;
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BSTree;
void CreateBiTree(BSTree &T,char a[],int &i)
{//先序建立二叉树
	if(a[i]=='#')
		T=NULL;
	else
	{
		T=new BiTNode;
		T->data=a[i];
		CreateBiTree(T->lchild,a,++i);
		CreateBiTree(T->rchild,a,++i);
	}
}
int Height(BSTree T)
{//求平衡二叉树T的高度
	int level=0;         			//记录树的高度
	BSTree p=T;
	while(p)
	{
		level++;          			//树的高度加1
		if(p->data<0)p=p->rchild;	//b=-1沿右分支向下
		else p=p->lchild;			//b>=0沿左分支向下
	}
	return level;  					//返回平衡二叉树的高度
}
int main()
{
	char a[100];	//如果平衡因子b=-1，会被字符数组割裂成'-'和'1'，故本题输入样例不包含b=-1
	while(cin>>a)
	{
		if(strcmp(a,"#")==0) break;
		int i=-1;
	  	BSTree T;
		CreateBiTree(T,a,++i);
		cout<<Height(T)<<endl;
	}
	return 0;
}
