//表示工程的有向图, 顶点表示活动, 弧表示活动间的优先关系, AOV网;
//拓扑排序即对1个有向图构造拓扑序列的过程;
//从AOV网中选择1个入度为0的顶点输出, 删除(包括依次为尾的弧), 重复至输出全部顶点/不存在入度为0的顶点;
#include<stdio.h>    
#include<stdlib.h>   
#include<math.h>  
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 14
#define MAXEDGE 20

typedef int Status;
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
}VertexNode, adjList[MAXVEX];

typedef struct
{
	adjList adjList;
	int numVertexes, numEdges;
}graphAdjList, *GraphAdjList;


//构建图;
Status CreateMGraph(MGraph *G)
{
	int i, j;
	G->numVertexes = MAXVEX;
	G->numEdges = MAXEDGE;
	
	for(i=0; i<G->numVertexes; i++)
		G->vexs[i] = i;
	for(i=0; i<G->numVertexes; i++)
	{
		for(j=0; j<G->numVertexes; j++)
			G->arc[i][j] = 0;
	}
	G->arc[0][4]=1;
	G->arc[0][5]=1; 
	G->arc[0][11]=1; 
	G->arc[1][2]=1; 
	G->arc[1][4]=1; 
	G->arc[1][8]=1; 
	G->arc[2][5]=1; 
	G->arc[2][6]=1;
	G->arc[2][9]=1;
	G->arc[3][2]=1; 
	G->arc[3][13]=1;
	G->arc[4][7]=1;
	G->arc[5][8]=1;
	G->arc[5][12]=1; 
	G->arc[6][5]=1; 
	G->arc[8][7]=1;
	G->arc[9][10]=1;
	G->arc[9][11]=1;
	G->arc[10][13]=1;
	G->arc[12][9]=1;
	
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
			if(G.arc[i][j]==1)
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
	while(top!=0)
	{
		gettop = stack[top--];
		printf("%d -> ", GL->adjList[gettop].data);
		count++;
		for(e=GL->adjList[gettop].firstedge; e; e=e->next)
		{
			k = e->adjvex;
			if(!(--GL->adjList[k].in))	//将i号顶点的邻接点的入度-1, 若-1后为0, 则入栈
				stack[++top] = k;
		}
	}
	printf("\n");
	if(count < GL->numVertexes)
		return ERROR;
	else
		return TRUE;
}

int main(void)
{
	MGraph G;
	GraphAdjList GL;
	int result;
	CreateMGraph(&G);
	CreateALGraph(G, &GL);
	result = TopologicalSort(GL);
	printf("result: %d", result);
	
	return 0;
}
