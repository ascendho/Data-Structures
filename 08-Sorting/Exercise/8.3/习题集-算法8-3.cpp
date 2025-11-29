#include<iostream>
using namespace std;

void Process(int a[],int n)
{//对数组a中的n个关键字进行整理
//使所有关键字为负值的记录排在关键字为非负值的记录之前
    int low=0,high=n-1;
    while(low<high)
    {
        while(low<high&&a[low]<0)            //找到从左到右的非负值记录 
			low++;    
        while(low<high&&a[high]>=0)           //找到从右到左的负值记录 
			high--;  
        if(low<high)                         //如果需要交换，即low<high
        {
           	int temp=a[low];
			a[low]=a[high];
			a[high]=temp;                    //交换记录 
            low++;                           //继续向后找
            high--;
        }
    }
}
void PrintA(int a[],int n)
{//输出数据
    for(int i=0;i<n-1;i++)
        cout<<a[i]<<" ";
    cout<<a[n-1]<<endl;
}
int main()
{
	
	int n;
	cout<<"请输入数组长度:";
	cin>>n;
	
	int *a=new int[n];
	cout<<"请输入关键字以空格隔开:";
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	
	Process(a,n);      //数组的正负排序
	cout<<"排序结果:";
    PrintA(a,n);       //输出数据

    return 0;
}

