#include <iostream>
#include <cstdlib>
using namespace std;

//函数结果状态代码 
#define OK 1
#define ERROR 0
#define OVERFLOW -2

//Status是函数的返回值类型，其值是函数结果状态代码
typedef int Status;

typedef struct DuLNode                                  //双向链表 
{
	int data;
	struct DuLNode *prior,*next;
}DuLNode, *DuLinkList;									

Status InitList(DuLinkList &L);							//初始化 
Status DestroyList(DuLinkList &L);						//销毁链表
void CreateList_R(DuLinkList &L,int L_Data[],int n);	//后插法创建双向链表
void DuplexSort(DuLinkList &L);                         //双向冒泡排序 
void PrintList(DuLinkList L);						    //输出链表 

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

	DuLinkList l;
	InitList(l);
	CreateList_R(l,lData,n);                     
	DuplexSort(l);
	cout<<"排序结果:";
	PrintList(l);

	delete(lData);
	DestroyList(l);
	
	return 0;
}

//初始化 
Status InitList(DuLinkList &L)
{//构造一个空的双向链表L 
    L=new DuLNode;                   //初始化链表L的头结点
	L->prior=L;
	L->next=L;
	return OK; 
} 

//销毁链表 
Status DestroyList(DuLinkList &L)
{
	while(L)
	{
		DuLNode *p=L;
		L=L->next;
		delete p;					//释放空间
	}
	return OK;
}

//后插法创建双向链表
void CreateList_R(DuLinkList &L,int L_Data[],int n)
{//正位序输入n个元素的值，建立带表头结点的双向链表L 

	DuLinkList p=new DuLNode;
	p->data=L_Data[0];
	L->next=p;
	p->prior=L;
	p->next=NULL;
	for(int i=1;i<n;i++)
	{
		DuLinkList p=new DuLNode;
		p->data=L_Data[i];
		p->prior=L;
		L->next->prior=p;
		p->next=L->next;
		L->next=p;
	}
}

//输出链表 
void PrintList(DuLinkList L)
{//依次输出链表中的数据
    DuLinkList p=L->next;
	while(p!=NULL)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
	
	
}
//双向冒泡排序
void DuplexSort(DuLinkList &L)
{ //对存储在带头结点的双向链表L中的元素进行双向冒泡排序
	int exchange=1;                                             //是否发生交换的标记                                      
	DuLinkList head,tail,p,temp;
	head=L;                                                     //双向链表头，向下冒泡的开始结点
	tail=NULL;                                                  //双向链表尾，向上冒泡的开始结点
	while(exchange)
	{
		if(head->next==tail) 
			break;
		p=head->next;                                           //p是工作指针，指向当前结点
		exchange=0;                                             //假定本趟无交换
		while(p->next!=tail)                                    //向下冒泡，每一趟使一最大元素沉底
		{
			if(p->data > p->next->data)                         //交换两结点指针，涉及6条链
			{
				temp=p->next;
				exchange=1;                                     //有交换
				p->next=temp->next;
				if(temp->next!=NULL)
					temp->next->prior=p;                        //先将结点从链表上摘下
				temp->next=p;
				p->prior->next=temp;                            //将temp插到结点*p前
				temp->prior=p->prior;
				p->prior=temp;
			}
			else p=p->next;                                     //无交换，指针后移
		}
		tail=p;                                                 //准备向上起泡
		p=tail->prior;
		while(exchange && p->prior!=head)
		{
			if(p->data < p->prior->data)                        //交换两结点指针，涉及6条链
			{
				temp=p->prior;
				exchange=1;                                     //有交换
            	p->prior=temp->prior;
            	temp->prior->next=p;                         	//先将temp结点从链表上摘下
            	temp->prior=p;
				p->next->prior=temp;        	                //将temp插到p结点后(右)
            	temp->next=p->next;
				p->next=temp;
			}
			else p=p->prior;                                    //无交换，指针前移
		}
		head=p;                                                 //准备向下起泡
	}                                                           //while(exchange)
} 

