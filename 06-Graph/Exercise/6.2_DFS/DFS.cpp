#include "DFS.h"
#include <iostream>

using namespace std;

void DFS(ALGraph G, int v) {
	SqStack S;
	InitStack(S);                                  	// 初始化栈
	Push(S, v);                                     // 入栈v
	while (!StackEmpty(S)) {						// 栈不空
		int k;
		Pop(S, k);                                       	    // 出栈，元素k出栈
		if (!visited[k]) {
			cout << k;                                     	    // 访问节点k
			visited[k] = true;
			ArcNode *p = G.vertices[k].firstarc;               	// p指向k的第一条边
			while (p != NULL) {
				int w = p->adjvex;                             	// w是k的邻接点
				if (!visited[w]) Push(S, w);            	    // 如果w未被访问，则入栈
				p = p->nextarc;                            	    // p指向下一条边
			}
		}
	}
	cout << endl;
}