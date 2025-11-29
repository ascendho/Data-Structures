#include<iostream>
#define LENGTH 7
using namespace std;
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*LinkList;
LinkList HT[LENGTH];
int H(int data)
{
	return data%LENGTH;
}
bool Insert_K( )
{
	int data;
	cin>>data;
	int ant=H(data);
	LinkList p=HT[ant];					//找到该散列地址代表的位置
	while(p->next)
	{//确定插入位置
		if(p->next->data==data)
		return false;
		p=p->next;
	}
	LinkList s=new LNode;
	s->data=data;
	s->next=p->next;
	p->next=s;                          //插入该结点置于链表尾部
	return true;
}
bool Delete_K()
{
	int data;
	cin>>data;
	int ant=H(data);
	LinkList p=HT[ant];     			//找到该散列地址代表的位置
	while(p->next)           			//确定删除位置
	{	
		if(p->next->data==data)
		{
			LinkList s=p->next;
			p->next=s->next;
			delete s;       			//删除该结点
			return true;
		} 
		p=p->next;         				//遍历下一个结点
	}
	return false;
}
void Output()
{//输出数据
	for(int i=0;i<LENGTH;i++)
	{
		cout<<i<<":";             		//输出散列地址
		LinkList p=HT[i]->next;  		//p初始化为链表的首元结点
		while(p)
		{
			cout<<p->data;
			p=p->next;
			if(p) cout<<" ";
		}
		cout<<endl;
	}
}
void initHash()
{
	for(int i=0;i<LENGTH;i++)
	{
		HT[i]=new LNode;
		HT[i]->next=NULL;
	}
}
int main()
{
	initHash();
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		Insert_K();
	Output();
	Delete_K();
	Output();
	return 0;
}
