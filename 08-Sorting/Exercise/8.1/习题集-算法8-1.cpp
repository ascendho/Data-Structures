#include <iostream>
#include <cstdlib>
using namespace std;

//函数结果状态代码 
#define OK 1
#define ERROR 0
#define OVERFLOW -2

//Status是函数的返回值类型，其值是函数结果状态代码
typedef int Status;

typedef struct LNode
{
	int data;											//结点的数据域 
	struct LNode *next;									//结点的指针域 
}LNode, *LinkList;										//LinkList为指向结构体LNode的指针类型

Status InitList(LinkList &L);							//初始化 
Status DestroyList(LinkList &L);						//销毁链表
void CreateList_R(LinkList &L,int L_Data[],int n);		//后插法创建单链表
void SelectSort(LinkList &L);	                        //简单选择排序 
void PrintList(LinkList L);								//输出链表 

int main()
{	
	int n;
	cout<<"请输入链表长度:";
	cin>>n;
	
	int *lData=new int[n];
	cout<<"请输入关键字以空格隔开:";
	for(int i=0;i<n;i++)
	{
		cin>>lData[i];
	}

	LinkList l;
	InitList(l);
	CreateList_R(l,lData,n);                             
	SelectSort(l);
	cout<<"排序结果:";
	PrintList(l);

	delete(lData);
	DestroyList(l);
	
	return 0;
}

//初始化 
Status InitList(LinkList &L)
{//构造一个空的单链表L 
	L=new LNode;					//生成新结点作为头结点，用头指针L指向头结点 
	L->next=NULL;					//头结点的指针域置空 
	return OK; 
} 

//销毁链表 
Status DestroyList(LinkList &L)
{
	while(L)
	{
		LNode *p=L;
		L=L->next;
		delete p;					//释放空间
	}
	return OK;
}

//后插法创建单链表
void CreateList_R(LinkList &L,int L_Data[],int n)
{//正位序输入n个元素的值，建立带表头结点的单链表L 
	LNode *r = L;					//尾指针r指向头结点
	for (int i=0;i<n;++i)
	{ 
		LNode *p=new LNode;			//生成新结点 
		p->data=L_Data[i];			//初始化p的数据域为L_Data[i]
		p->next=NULL; r->next=p;	//将新结点*p插入尾结点*r之后 
		r=p;						//r指向新的尾结点*p
	}
}

//输出链表 
void PrintList(LinkList L)
{
	LNode *p=L;
	p=p->next;
	while(p)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
}

//简单选择排序 
void SelectSort(LinkList &L)
{//基于单链表的简单选择排序
	LNode *p=L->next;				//p指向首元结点
	while(p!=NULL)                  //顺链域向后扫描，直到p为空
	{
		LNode *q=p->next;
		LNode *r=p;                 //r是指向关键字最小的结点的指针
		while(q!=NULL)
		{
			if(q->data<r->data)
				r=q;
         	q=q->next;
		}
		if(r!=p)                    //交换r和p的数据域
		{
			int temp=r->data;
			r->data=p->data;
			p->data=temp;
		}
		p=p->next;                  //p指向下一个结点
	}
}
