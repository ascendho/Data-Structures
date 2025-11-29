#include<iostream>
using namespace std;
void CountSort(int a[],int b[],int n)
{//计数排序,将包括n个数据的数组a中的记录排序存入到数组b中
    int i,j,c;
    for(i=0;i<n;i++)               //针对数组中的每个关键字
    {
        for(j=0,c=0;j<n;j++)       //统计关键字比当前关键字小的元素个数
            if(a[j]<a[i]) c++;
        b[c]=a[i];                 //根据比当前关键字小的元素个数将当前关键字存放在数组b中
    }
}
int main()
{
	
	int n;
	cout<<"请输入数组长度:";
	cin>>n;
	
	int i,a[100],b[100];
	cout<<"请输入关键字以空格隔开:";
    for(i=0;i<n;i++)
        cin>>a[i];
    
    CountSort(a,b,n);     //计数排序
   	cout<<"排序结果:";
    for(i=0;i<n-1;i++)
        cout<<b[i]<<" ";
    cout<<b[n-1]<<endl;
    
}
