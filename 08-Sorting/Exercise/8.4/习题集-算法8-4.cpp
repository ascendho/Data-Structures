//基于快排思想的查找
#include <iostream>
using namespace std;
int  Search(int r[],int low,int high,int key)
{//在数组r[low..high]中查找关键字值等于key的记录
	while(low<high)
	{
		if(r[low]>key&&r[high]<key)
		{
			low++;
			high--;
		}
		while(low<=high && r[high]>key) high--;
		//从右侧开始找到第一个不大于关键字的记录，其位置为high
		if(r[high]==key)						//查找成功返回其位置
			return high;
		while(low<=high && r[low]<key)	low++;
		//从左侧开始找到第一个不小于关键字的记录，其位置为low
		if(r[low]==key)							//查找成功返回其位置
			return low;
	}
	cout<<"Not find"<<endl;						//查找失败
	return -1;
}
int main()
{
	int n;
	cout<<"请输入数组长度：";
	cin>>n;
	 
	int r[n];
	cout<<"请输入数组元素：";
	for(int i=0;i<n;i++)
		cin>>r[i];
		
	int key;
	cout<<"请输入要查找的元素：";
	cin>>key;
	
	int p=Search(r,0,n-1,key);//查找
	if(p!=-1)
		cout<<"该元素在数组中的位置为："<<p+1<<endl;

	return 0;
} 
