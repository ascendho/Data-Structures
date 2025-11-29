//邻接矩阵存储带权无向图
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
#define MaxInt 0x7fffffff

//定义图的结构体类型
typedef struct {
	int vexs[MVNum + 1];	//顶点集	因为顶点存储序号范围为1~MVNum
	int arcs[MVNum + 1][MVNum + 1];		//邻接矩阵
	int vexnum, arcnum;	//图当前的顶点数和边数
}AMGraph;

bool S[MVNum + 1];
int D[MVNum + 1];
int Path[MVNum + 1];

//采用邻接矩阵表示法，创建无向图graph
Status createUDN(AMGraph &graph, int vexnum, int arcnum) {
	graph.vexnum = vexnum;		//初始化图的总顶点数
	graph.arcnum = arcnum;		//初始化图的总边数
	if (graph.vexnum >= MVNum) return ERROR;	//顶点数超过最大允许范围，返回错误代码。(注意数组下标从0开始)
	for (int i = 0; i <= graph.vexnum; i++) {	//依次输入顶点信息
		graph.vexs[i] = i;
	}
	for (int i = 0; i <= graph.vexnum; i++) {	//初始化所有边的权值为0，表示边不存在
		for (int j = 0; j <= graph.vexnum; j++) {
			graph.arcs[i][j] = 0;
		}
	}
	int vex_one, vex_two, weight;	//一条边依附的两个顶点vex_one和vex_two
	for (int i = 0; i < graph.arcnum; i++) {	//循环输入arcnum条边的信息
		cin >> vex_one >> vex_two >> weight;
		graph.arcs[vex_one][vex_two] = weight;	//表权值为1，表示边存在
		graph.arcs[vex_two][vex_one] = weight;
	}
	return OK;	//创建成功，返回成功代码。
}

//定义打印无向图函数
void printUDN(AMGraph graph) {
	for (int i = 0; i <= graph.vexnum; i++) {	//在第一行打印顶点信息
		cout << graph.vexs[i] << " ";
	}
	cout << endl;
	for (int i = 1; i <= graph.vexnum; i++) {	//输出边的信息（每行第一个数字为顶点）（注意0号顶点不输出）
		cout << graph.vexs[i] << " ";	//输出该行对应的顶点
		for (int j = 1; j <= graph.vexnum; j++) {	//输出该行顶点对应所有边信息
			cout << graph.arcs[i][j] << " ";
		}
		cout << endl;
	}
	//输出结束
}

//用Dijkstra算法求图G中距离顶点v0的最短路径长度最大的一个顶点m 
int ShortestPathMAX(AMGraph G, int v0) {
	int n = G.vexnum;                             	//n为G中顶点的个数
	for (int v = 1; v <= n; v++) {
		S[v] = false;		//S初始为空集 
		D[v] = G.arcs[v0][v];                 	//将v0到各个终点的最短路径长度初始化为弧上的权值
		if (D[v] == 0) D[v] = MaxInt;
		if (D[v] < MaxInt) Path[v] = v0;       	//如果v0和v之间有弧，则将v的前驱置为v0
		else Path[v] = -1;                    	//如果v0和v之间无弧，则将v的前驱置为-1 
	}//end for
	S[v0] = true;                             	//将v0加入S 
	D[v0] = 0;                                 	//源点到源点的距离为0 
	/*--------初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集---------*/
	for (int i = 1; i < n; i++) {		//对其余n−1个顶点，依次进行计算
		int min = MaxInt, v;
		for (int w = 1; w <= n; w++) {		//选择一条当前的最短路径，终点为v
			if (!S[w] && D[w] < min) { 
				v = w;
				min = D[w];
			}
		}
		S[v] = true;
		for (int w = 1; w <= n; w++) {
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w])) {	//更新从v0出发到集合V−S上所有顶点的最短路径长度
				D[w] = D[v] + G.arcs[v][w];    	//更新D[w] 
				Path[w] = v;                    	//更改w的前驱为v 
			}// end if
		}// end for
	}//end for
	 /*-----------最短路径求解完毕，设距离顶点v0的最短路径长度最大的一个顶点为m--------------*/
	int Max = D[1];
	int m = 1;
	for (int i = 2; i <= n; i++)
		if (Max < D[i]) 
			m = i;
	return m;                               	//返回顶点下标
}

int main() {
	int n, m, w;
	cout << "请输入顶点的数量n和边的数量m（空格分隔，下同）： \b";
	cin >> n >> m;		//输入n和m的值
	AMGraph G;
	cout << "请依次输入m条边所依附的两端顶点以及边权重：\n";
	createUDN(G, n, m);
	//打印图的信息
	printUDN(G);
	int v;
	cout << "请输入开始顶点编号： \b";
	cin >> v;
	cout << ShortestPathMAX(G, v) << endl;
	system("pause");
	return 0;	//程序运行结束
}