#include "Width.h"
#include <stdio.h>

int Width(BiTree T)
{   // 求二叉树T的最大宽度
   if(T==NULL) 
      return 0;                          	// 空二叉树的宽度为0
   else 
   {
      BiTree Q[100];                        // Q是队列，元素为二叉树结点指针，容量足够大
      int front=1;                          // 头指针
      int rear=1;                           // 尾指针
      int last=1;                           // 同层最右结点在队列中的位置
      int temp=0;                           // 局部宽度
      int maxw=0;                           // 最大宽度
      Q[rear]=T;                        	// 根结点入队
      while(front<=last)
      {
         BiTree p=Q[front++];
         temp++; 						    // 同层元素加1
         if(p->lchild!=NULL)  
            Q[++rear]=p->lchild;        	// 左孩子入队
         if(p->rchild!=NULL)  
            Q[++rear]=p->rchild;        	// 右孩子入队
         if(front>last)                 	// 一层结束
         {
            last=rear;                    	// last指向下层最右元素
            if(temp>maxw) maxw=temp;   	    // 更新最大宽度
            temp=0;
         }                                 	// if
      }                                    	// while
      return maxw;
   }
}