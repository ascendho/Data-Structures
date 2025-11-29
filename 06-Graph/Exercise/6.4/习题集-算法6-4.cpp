//邻接表存储有向图
#include <iostream>
using namespace std;

//定义最大顶点数
#define MVNum 128
//定义状态类型
#define Status int
//函数结果状态代码 
#define OK 1
#define ERROR 0
#define INFEASIBLE 0
#define EXISTED 2

typedef struct ArcNode {		//定义边结点
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VexNode {		//定义顶点结点
	int data;
	struct ArcNode *firstarc;
}VexNode;

typedef struct ALGraph {	//定义图的结构体类型
	VexNode vertices[MVNum + 1];
	int vexnum, arcnum;	//图当前的顶点数和边数
}ALGraph;

int visited[MVNum] = { 0 };                        	//访问标志数组，其初值为false
int level = 1;                              	//递归进行的层数

//对于每个顶点，它的边采用头插法插入
void insertArcNode(VexNode &vnode, int adjvex) {	//向邻接表顶点中插入一条边结点
	ArcNode *arcnode = new ArcNode;
	arcnode->adjvex = adjvex;
	arcnode->nextarc = vnode.firstarc;
	vnode.firstarc = arcnode;
}

//采用邻接矩阵表示法，创建无向图graph
Status createGraph(ALGraph &graph, int vexnum, int arcnum) {
	graph.vexnum = vexnum;      //初始化图的总顶点数  
	graph.arcnum = arcnum;     //初始化图的总边数  
	for (int i = 0; i <= graph.vexnum; i++) {	//初始图中的顶点信息
		graph.vertices[i].data = i;
		graph.vertices[i].firstarc = NULL;
	}
	int vex_one, vex_two;	//一条边依附的两个顶点vex_one和vex_two 
	for (int i = 0; i < graph.arcnum; i++) {	//循环输入arcnum条边的信息
		cin >> vex_one >> vex_two;
		insertArcNode(graph.vertices[vex_one], vex_two);
	}
	return OK;  //创建成功，返回成功代码
}

//定义打印邮箱向图函数  
void printGraph(ALGraph graph) {
	for (int i = 1; i <= graph.vexnum; i++) {	//输出边的信息（每行第一个数字为顶点）（注意0号顶点不输出）  
		cout << graph.vertices[i].data << " ";
		for (ArcNode *p = graph.vertices[i].firstarc; p; p = p->nextarc) {	//开始输出每个顶点上所链接的边信息
			cout << p->adjvex << " ";
		}
		cout << endl;
	}
	//输出结束
}

//基于深度优先搜索判断有向图G中顶点i到顶点j是否有路径，是则返回1，否则返回0
int PathDFS(ALGraph G, int i, int j) {
	if (i == j) return 1;                     	//递归结束的条件，首尾相遇，存在路径
	else {
		visited[i] = true;                    	//顶点i访问标志为true
		for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc, level--) {
			level++;                          	//递归层次加1
			int k = p->adjvex;
			if (!visited[k] && PathDFS(G, k, j))
				return 1;                      	//i下游的顶点到j有路径 
		}//end for
	}//end else
	return 0;                 	//i到j没有路径
}

int main() {
	int n, m;		//n个顶点和m条边
	cout << "请输入顶点的数量n和边的数量m（空格分隔，下同）： \b";
	cin >> n >> m;      //输入n和m的值  
	ALGraph G;
	cout << "请依次输入m条边所依附的起点和终点：\n";
	createGraph(G, n, m);
	//打印图的信息  
	printGraph(G);
	cout << "请输入需遍历路径的起点和终点： \b";
	int start, destination;
	cin >> start >> destination;
	int result = PathDFS(G, start, destination);
	if (result)
		cout << "有路径" << endl;
	else
		cout << "没有路径" << endl;
	system("pause");
	return 0;
}