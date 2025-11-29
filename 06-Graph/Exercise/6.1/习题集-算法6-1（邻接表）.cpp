//邻接链表存储图
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

typedef struct ArcNode{		//定义边结点
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;

typedef struct VexNode{		//定义顶点结点
	int data;
	struct ArcNode *firstarc;
}VexNode;

typedef struct ALGraph{	//定义图的结构体类型
	VexNode vertices[MVNum + 1];
	int vexnum, arcnum;	//图当前的顶点数和边数
}ALGraph;

//对于每个顶点，它的边采用头插法插入
void insertArcNode(VexNode &vnode, int adjvex) {	//向邻接表顶点中插入一条边结点
	ArcNode *arcnode = new ArcNode;
	arcnode->adjvex = adjvex;
	arcnode->nextarc = vnode.firstarc;
	vnode.firstarc = arcnode;
}

//采用邻接矩阵表示法，创建无向图graph
Status createUDN(ALGraph &graph, int vexnum, int arcnum) {
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
		insertArcNode(graph.vertices[vex_two], vex_one);
	}
	return OK;  //创建成功，返回成功代码
}

//定义打印无向图函数  
void printUDN(ALGraph graph) {
	for (int i = 1; i <= graph.vexnum; i++) {	//输出边的信息（每行第一个数字为顶点）（注意0号顶点不输出）  
		cout << graph.vertices[i].data << " ";
		for (ArcNode *p = graph.vertices[i].firstarc; p; p = p->nextarc) {	//开始输出每个顶点上所链接的边信息
			cout << p->adjvex << " ";
		}
		cout << endl;
	}
	//输出结束
}

//判断顶点v是否存在图G中
int LocateVex(ALGraph G, int v) {
	for (int i = 0; i <= G.vexnum; i++) {
		if (G.vertices[i].data == v)
			return i;
	}
	return -1;
}

//在以邻接表形式存储的无向图G上插入顶点v
Status InsertVex(ALGraph &G, int v) {
	if (LocateVex(G, v) >= 0)return EXISTED; //判断该顶点是否已存在 
	if ((G.vexnum + 1) > MVNum)return INFEASIBLE;                          	//判断插入操作是否合法
	G.vexnum++;		//增加图的顶点数量
	G.vertices[G.vexnum].data = v;                 	//新顶点对应的链表的头结点数据域赋值为v
	G.vertices[G.vexnum].firstarc = NULL;         	//指针域赋值为NULL
	return OK;		//添加成功，返回成功代码
}

//在以邻接表形式存储的无向图G上删除顶点v
Status DeleteVex(ALGraph &G, int v) {
	int n;
	if ((n = LocateVex(G, v)) < 0)return ERROR;		//表示删除的顶点v不存在
	//首先删除顶点v依附的边结点
	for (ArcNode *p = G.vertices[n].firstarc; p; p = G.vertices[n].firstarc) {
		G.vertices[n].firstarc = p->nextarc;
		delete p;
		G.arcnum--;	//每删除一条边，边数量减一，下图中遍历邻接表删除边时则不用再自减
	}
	//随后把v的顶点信息删除，后面顶点向前移动
	for (int i = n; i < G.vexnum; i++) {
		G.vertices[i] = G.vertices[i + 1];
	}
	G.vexnum--;		//顶点数量减一
	//最后遍历所有顶点，将与顶点v关联的边结点删除
	for (int i = 1; i <= G.vexnum; i++) {
		VexNode p = G.vertices[i], q = G.vertices[i];           	//p指向当前结点的前驱，q指向当前结点
		if (!p.firstarc)continue;	//如果该顶点上没有边，需要自动跳过
		if (p.firstarc->adjvex == v)	//如果当前结点的第一条边关联的结点为v，则直接删除该边
		{
			ArcNode *temp = G.vertices[i].firstarc->nextarc;
			delete G.vertices[i].firstarc;
			G.vertices[i].firstarc = temp;
			continue;
		}
		q.firstarc = p.firstarc->nextarc;           	//继续比较后面的边结点
		while (q.firstarc) {	
			if (q.firstarc->adjvex == v) {		//存在与v相关联的边，则删除该边
				ArcNode *temp = q.firstarc;
				p.firstarc->nextarc = q.firstarc->nextarc;
				delete temp;
				break;
			}
			p.firstarc = q.firstarc;		//没找到与v相关联的边，p和q指针均后移
			q.firstarc = q.firstarc->nextarc;	
		}
	}
	return OK;		//删除成功，返回成功代码
}

//在以邻接表形式存储的无向图G上插入边(v,w)
Status InsertArc(ALGraph &G, int v, int w) {
	int i, j;
	i = LocateVex(G, v);								//确定v和w在G中的位置
	j = LocateVex(G, w);                               	
	if (i <= 0) return ERROR;                         	//判断插入位置是否合法
	if (j <= 0) return ERROR;
	ArcNode *p1 = new ArcNode;							//生成一个新的边结点*p1
	p1->adjvex = w;                                   	//邻接点序号为j
	p1->nextarc = G.vertices[i].firstarc;				//将新结点*p1插入顶点v的边表头部
	G.vertices[i].firstarc = p1;                   		
	ArcNode *p2 = new ArcNode;							//生成一个新的边结点*p1
	p2->adjvex = v;                                   	//邻接点序号为j
	p2->nextarc = G.vertices[j].firstarc;				//将新结点*p2插入顶点w的边表头部
	G.vertices[j].firstarc = p2;
	G.arcnum++;
	return OK;			//插入成功，返回插入成功代码
}

//在以邻接表形式存储的无向图G上删除边<v,w>
Status DeleteArc(ALGraph &G, int v, int w) {
	int i, j;
	i = LocateVex(G, v);								//确定v和w在G中的位置
	j = LocateVex(G, w);
	if (i <= 0) return ERROR;                         	//判断删除位置是否合法
	if (j <= 0) return ERROR;
	//从顶点v所在的边链表遍历链表进行查找，第一个边结点是(v,w)，直接删除
	if (G.vertices[i].firstarc->adjvex == w) {
		ArcNode *temp = G.vertices[i].firstarc->nextarc;
		delete G.vertices[i].firstarc;
		G.vertices[i].firstarc = temp;
	}
	else {	//第一个边结点不是(v,w)，继续向后查找(v,w)
		ArcNode *p1 = G.vertices[i].firstarc, *p2 = G.vertices[i].firstarc;
		while (p2->nextarc) {
			if (p2->adjvex == w) {		//在链表中找到边结点(v,w)
				p1->nextarc = p2->nextarc;
				delete p2;
				break;
			}
			p1 = p2;
			p2 = p2->nextarc;
		}
	}
	//从顶点w所在的边链表遍历链表进行查找，第一个边结点是(w,v)，直接删除
	if (G.vertices[j].firstarc->adjvex == v) {
		ArcNode *temp = G.vertices[j].firstarc->nextarc;
		delete G.vertices[j].firstarc;
		G.vertices[j].firstarc = temp;
	}
	else {	//第一个边结点不是(v,w)，继续向后查找(v,w)
		ArcNode *p1 = G.vertices[j].firstarc, *p2 = G.vertices[j].firstarc;
		while (p2->nextarc) {
			if (p2->adjvex ==v) {		//在链表中找到边结点(v,w)
				p1->nextarc = p2->nextarc;
				delete p2;
				break;
			}
			p1 = p2;
			p2 = p2->nextarc;
		}
	}
	G.arcnum--;                                     	//边的数目减1
	return OK;		//删除成功，返回成功代码
}

int main() {
	int n, m;		//n个顶点和m条边
	cout << "请输入顶点的数量n和边的数量m（空格分隔，下同）： \b";
	cin >> n >> m;      //输入n和m的值  
	ALGraph G;
	cout << "请依次输入m条边所依附的两端顶点：\n";
	createUDN(G, n, m);
	//打印图的信息  
	printUDN(G);
	int v, w;
	//开始添加新顶点测试  
	cout << "请输入待添加新顶点编号： \b" << endl;
	cin >> v;
	InsertVex(G, v);    //插入顶点v
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