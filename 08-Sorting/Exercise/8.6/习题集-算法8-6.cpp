#include<iostream>
using namespace std;

int Partition(int a[],int n)
{//将正整数构成的集合划分为两个不相交的子集A1和A2
	int low=0,high=n-1;								//分别指向表的下界和上界
	int low0=0,high0=n-1;							//分别指向新的子表的下界和上界
	int s1=0,s2=0;									//分别记录A1和A2中元素的和
	int flag=1;										//标记划分是否成功
	int k=n/2;										//记录表的中间位置
	while(flag)										//循环进行划分
	{
		int pivotkey=a[low];						//选择枢轴
		while(low<high)								//从两端交替地向中间扫描
		{
			while(low<high && a[high]>=pivotkey)
				--high;								//从最右侧位置依次向左搜索
			if(low!=high)
				a[low]=a[high];						//将比枢轴记录小的记录移到低端
			while(low<high && a[low]<=pivotkey)
				++low;								//从最左侧位置依次向右搜索
			if(low!=high)
				a[high]=a[low];						//将比枢轴记录大的记录移到高端
		}	
		a[low]=pivotkey;              				//枢轴记录到位
    	if(low==k-1)                   				//满足条件①，枢轴的位置是n/2的前一位置，
        	flag=0;                      			//划分成功，下次循环将退出划分
      	else                            			//继续划分
      	{
        	if(low<k-1)                				//满足条件②，枢轴low及之前的所有元素均属于A1
         	{
            	low0=++low;              			//继续对low之后的元素进行划分
            	high=high0;
         	}
         	else                         			//满足条件③，枢轴low及之后的所有元素均属于A2
         	{
            	high0=--high;           			//继续对low之前的元素进行划分
            	low=low0;
         	}
       }
  	}
	  	
  	cout<<"A1中的元素：";
   	for(int i=0;i<k;i++)
   	{
   		cout<<a[i]<<" ";
   		s1+=a[i];    	//求解子集A1中元素的和
	}
	cout<<endl;
	
	cout<<"A2中的元素：" ;
   	for(int i=k;i<n;i++)
   	{
   		cout<<a[i]<<" ";
   		s2+=a[i];    	//求解子集A2中元素的和
   	}
   	cout<<endl;
   	
   	cout<<"|S1-S2|的值为："<<s2-s1<<endl; 
   	return s2-s1;
}

int main()
{
	int n;
	cout<<"请输入数组长度：";
	cin>>n;
	 
	int a[n];
	cout<<"请输入数组元素：";
	for(int i=0;i<n;i++)
		cin>>a[i];
	
	Partition(a,n);
		
	return 0;
}
