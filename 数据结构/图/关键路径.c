//表示工程的有向图, 顶点表示时间, 弧表示活动, 权值表示持续时间, AOE网;
//路径上各活动所持续的时间之和: 路径长度;
//从源点到汇点具有最大长度路径: 关键路径, 在其上的活动叫关键活动;
#include<stdio.h>    
#include<stdlib.h>   
#include<math.h>  
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 30
#define MAXEDGE 30
#define GRAPH_INFINITY 65535

typedef int Status;
int *etv, *ltv;		//事件最早发生时间和最迟发生时间数组
int *stack2;		//存储拓扑结构序列的栈
int top2;			//栈指针下标

typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef struct EdgeNode		//边表结点
{
	int adjvex;			//邻接点域, 存储该结点对应下标
	int weight;			//存储权值
	struct EdgeNode *next;	//链域, 指向下一个邻接点
}EdgeNode;

typedef struct VertexNode	//顶点表结点
{
	int in;		//入度
	int data;	//顶点域, 存储顶点信息
	EdgeNode *firstedge;	//边表头结点
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes, numEdges;
}graphAdjList, *GraphAdjList;

//构建图;
Status CreateMGraph(MGraph *G)
{
	int i, j;
	G->numVertexes = 10;
	G->numEdges = 13;
	
	for(i=0; i<G->numVertexes; i++)
		G->vexs[i] = i;
	for(i=0; i<G->numVertexes; i++)
	{
		for(j=0; j<G->numVertexes; j++)
			G->arc[i][j] = 0;
	}
	G->arc[0][1]=3;
	G->arc[0][2]=4; 
	G->arc[1][3]=5; 
	G->arc[1][4]=6; 
	G->arc[2][3]=8; 
	G->arc[2][5]=7; 
	G->arc[3][4]=3;
	G->arc[4][6]=9; 
	G->arc[4][7]=4;
	G->arc[5][7]=6; 
	G->arc[6][9]=2;
	G->arc[7][8]=5;
	G->arc[8][9]=3;
	
	return OK;
}

//利用邻接矩阵构建邻接表;
Status CreateALGraph(MGraph G, GraphAdjList *GL)
{
	int i, j;
	EdgeNode *e;
	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));
	(*GL)->numVertexes = G.numVertexes;
	(*GL)->numEdges = G.numEdges;
	for(i=0; i<G.numVertexes; i++)		//建立顶点表
	{
		(*GL)->adjList[i].in = 0;
		(*GL)->adjList[i].data = G.vexs[i];
		(*GL)->adjList[i].firstedge = NULL;
	}
	for(i=0; i<G.numVertexes; i++)		//建立边表
	{
		for(j=0; j<G.numVertexes; j++)
		{
			if(G.arc[i][j]!=0 && G.arc[i][j]<GRAPH_INFINITY)
			{
				e = (EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex = j;			//邻接序号为1
				e->next = (*GL)->adjList[i].firstedge;
				(*GL)->adjList[i].firstedge = e;
				(*GL)->adjList[j].in++;
			}
		}
	}
	return OK;
}

Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;		//栈指针下标
	int count = 0;		//统计输出顶点的个数
	int *stack;			//建栈将入度为0的顶点入栈
	stack = (int*)malloc(GL->numVertexes *sizeof(int));
	
	for(i=0; i<GL->numVertexes; i++)
		if(0 == GL->adjList[i].in)		//入度为0的顶点入栈
			stack[++top] = i;
	top2 = 0;
	etv = (int*)malloc(GL->numVertexes *sizeof(int));
	for(i=0; i<GL->numVertexes; i++)
		etv[i] = 0;
	stack2 = (int*)malloc(GL->numVertexes *sizeof(int));
	
	printf("TopologicalSort:\t");
	while(top!=0)
	{
		gettop = stack[top--];
		printf("%d -> ", GL->adjList[gettop].data);
		count++;
		
		stack2[++top2] = gettop;	//将弹出的顶点序号压入拓扑序列的栈
		for(e=GL->adjList[gettop].firstedge; e; e=e->next)
		{
			k = e->adjvex;
			if(!(--GL->adjList[k].in))	//将i号顶点的邻接点的入度-1, 若-1后为0, 则入栈
				stack[++top] = k;
			if((etv[gettop]+e->weight)>etv[k])
				etv[k] = etv[gettop]+e->weight;
		}
	}
	return OK;
}

//求关键路径, GL为有向网, 输出G的各项关键活动;
Status CriticalPath(GraphAdjList GL)
{
	EdgeNode *e;
	int i, j, k, gettop;
	int ete, lte;			//活动最早发生和最迟发生的时间
	TopologicalSort(GL);	//计算数组etv和stack2的值
	ltv = (int *)malloc(GL->numVertexes *sizeof(int));
	for(i=0; i<GL->numVertexes; i++)
		ltv[i] = etv[GL->numVertexes-1];
	
	printf("etv:\n");
	for(i=0; i<GL->numVertexes; i++)
		printf("%d -> ", etv[i]);
	printf("\n");
	
	while(top2!=0)		//出栈是求ltv
	{
		gettop = stack2[top2--];
		for(e=GL->adjList[gettop].firstedge; e; e=e->next)	//求各项顶点事件最迟发生时间ltv
		{
			k = e->adjvex;
			if(ltv[k]-e->weight < ltv[gettop])
				ltv[gettop] = ltv[k]-e->weight;
		}
	}
	printf("ltv:\n");
	for(i=0; i<GL->numVertexes; i++)
		printf("%d -> ", ltv[i]);
	printf("\n");
	
	for(j=0; j<GL->numVertexes; j++)
	{
		for(e=GL->adjList[j].firstedge; e; e=e->next)
		{
			k = e->adjvex;
			ete = etv[j];		//活动最早发生时间
			lte = ltv[k]-e->weight;		//活动最迟发生时间
			if(ete==lte)
				printf("<v%d - v%d> length: %d \n", GL->adjList[j].data, GL->adjList[k].data, e->weight);
		}
	}
	return OK;
}

int main(void)
{    
	MGraph G;    
	GraphAdjList GL;    
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	CriticalPath(GL);
	
	return 0;
}
