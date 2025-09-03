#define MVNum 128

// 边表结点
typedef struct ArcNode {
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;

// 顶点表结点
typedef struct VexNode {
	int data;
	struct ArcNode *firstarc;
}VexNode;

// 邻接表图的结构定义
typedef struct ALGraph {
	VexNode vertices[MVNum + 1];
	int vexnum, arcnum;	            // 图当前的顶点数和边数
}ALGraph;

bool visited[MVNum] = { 0 };

// 递归栈的结构定义
typedef struct SqStack {
	int top;
	int vextics[MVNum + 1];
}SqStack;

// 初始化栈
void InitStack(SqStack &s) {
	s.top = -1;
}

// 入栈
int Push(SqStack &s, int v) {
	if (s.top == MVNum) return 0;	// 栈满，无法入栈
	s.vextics[++s.top] = v;
	return 1;
}

// 出栈
int Pop(SqStack &s, int &k) {
	if (s.top == -1)return 0;	   // 栈空，无法出栈
	k = s.vextics[s.top--];
	return 1;
}

// 判断栈是否为空
bool StackEmpty(SqStack s) {
	return s.top == -1;
}

void DFS(ALGraph G, int v);