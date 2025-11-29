//邻接矩阵存储图
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

//定义图的结构体类型
typedef struct {
	int vexs[MVNum + 1];	//顶点集	因为顶点存储序号范围为1~MVNum
	int arcs[MVNum + 1][MVNum + 1];		//邻接矩阵
	int vexnum, arcnum;	//图当前的顶点数和边数
}AMGraph;

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
	int vex_one, vex_two;	//一条边依附的两个顶点vex_one和vex_two
	for (int i = 0; i < graph.arcnum; i++) {	//循环输入arcnum条边的信息
		cin >> vex_one >> vex_two;
		graph.arcs[vex_one][vex_two] = 1;	//表权值为1，表示边存在
		graph.arcs[vex_two][vex_one] = 1;
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

int LocateVex(AMGraph G, int v) {	//判断顶点v是否存在图G中
	for (int i = 0; i <= G.vexnum; i++) {
		if (G.vexs[i] == v)
			return i;
	}
	return -1;
}

//增加一个新顶点v，InsertVex(G, v)；
//在以邻接矩阵形式存储的无向图G上插入顶点v
Status InsertVex(AMGraph &G, int v) {
	if (LocateVex(G, v) >= 0)return EXISTED;	//判断该顶点是否已存在
	if ((G.vexnum + 1) > MVNum)return INFEASIBLE;	//判断顶点数量是否已超过数组最大存储容量
	G.vexnum++;
	G.vexs[G.vexnum] = v;		//将顶点信息插入图的顶点数组中同时顶点数量自增加一
	for (int k = 0; k <= G.vexnum; k++) {
		G.arcs[G.vexnum][k] = G.arcs[k][G.vexnum] = 0;	//邻接矩阵中相应边的信息置为0
	}
	return OK;	//添加成功，返回成功代码
}

//删除顶点v及其相关的边，DeleteVex(G, v)；
//在以邻接矩阵形式存储的无向图G上删除顶点v以及和顶点相关的边
Status DeleteVex(AMGraph &G, int v) {
	int n = G.vexnum, m;	//m用于记录顶点v的数组存储下标位置
	if ((m = LocateVex(G, v)) < 0)	//判断删除操作是否合法，即v是否在G中
		return ERROR;
	int temp = G.vexs[m];	//将待删除顶点交换到最后一个顶点
	G.vexs[m] = G.vexs[n];
	G.vexs[n] = temp;
	for (int i = 0; i <= n; i++) {	//将边的关系也随之变换
		temp = G.arcs[m][i];
		G.arcs[m][i] = G.arcs[n][i];
		G.arcs[n][i] = temp;
		temp = G.arcs[i][m];
		G.arcs[i][m] = G.arcs[i][n];
		G.arcs[i][n] = temp;
	}
	G.vexnum--;		//顶点总数减一
	return OK;	//添加成功，返回成功代码
}

//增加一条边<v, w>，InsertArc(G, v, w)；
//在以邻接矩阵形式存储的无向图G上增加一条依附于顶点v和顶点m的边
Status InsertArc(AMGraph &G, int v, int w) {
	int i, j;
	if ((i = LocateVex(G, v)) < 0)return ERROR;		//判断插入位置是否合法
	if ((j = LocateVex(G, w)) < 0)return ERROR;
	if (i == j)return ERROR;
	if (G.arcs[i][j])return EXISTED;	//依附于顶点v和w的边已经存在
	G.arcs[i][j] = G.arcs[j][i] = 1;
	G.arcnum++;	//图的边数量加一
	return OK;	//添加成功，返回成功代码
}

//删除一条边<v, w>，DeleteArc(G, v, w)。
//在以邻接矩阵形式存储的无向图G上删除一条依附于顶点v和顶点m的边
Status DeleteArc(AMGraph &G, int v, int w) {
	int i, j;
	if ((i = LocateVex(G, v)) < 0)return ERROR;		//判断插入位置是否合法
	if ((j = LocateVex(G, w)) < 0)return ERROR;
	if (i == j)return ERROR;
	if (G.arcs[i][j] == 0)return INFEASIBLE;	//待删除的边不存在，返回非法错误
	G.arcs[i][j] = G.arcs[j][i] = 0;
	G.arcnum++;	//图的边数量加一
	return OK;	//添加成功，返回成功代码
}


int main() {
	int n, m;		//n个顶点和m条边
	cout << "请输入顶点的数量n和边的数量m（空格分隔，下同）： \b";
	cin >> n >> m;		//输入n和m的值
	AMGraph G;
	cout << "请依次输入m条边所依附的两端顶点：\n";
	createUDN(G, n, m);
	//打印图的信息
	printUDN(G);
	int v, w;
	//开始添加新顶点测试
	cout << "请输入待添加新顶点编号： \b" << endl;
	cin >> v;
	InsertVex(G, v);	//插入顶点v
						//打印图的信息
	printUDN(G);
	//开始删除顶点测试
	cout << "请输入待删除新顶点编号：\b" << endl;
	cin >> v;
	DeleteVex(G, v);
	//打印图的信息
	printUDN(G);
	//开始添加边的信息
	cout << "请输入待添加新边两端顶点的编号： \b" << endl;
	cin >> v >> w;
	InsertArc(G, v, w);
	//打印图的信息
	printUDN(G);
	//开始删除边的信息
	cout << "请输入待删除新边两端顶点的编号： \b" << endl;
	cin >> v >> w;
	DeleteArc(G, v, w);
	//打印图的信息
	printUDN(G);
	system("pause");
	return 0;	//程序运行结束
}