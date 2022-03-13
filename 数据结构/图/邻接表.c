#include<stdio.h>    
#include<stdlib.h>   
#include<math.h>  
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100				//最大顶点数

typedef int Status;			//函数结果状态代码
typedef char VertexType;	//顶点类型
typedef int EdgeType;		//权值类型

typedef struct EdgeNode		//边表结点
{
	int adjvex;			//邻接点域, 存储邻接点在顶点表中的下标
	EdgeType info;		//存储权值
	struct EdgeNode *next;		//链域, 指向下一个邻接点
}EdgeNode;

typedef struct VertexNode	//顶点表结点
{
	VertexType data;		//顶点域, 存储顶点信息
	EdgeNode *firstedge;	//边表头指针
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numNodes, numEdges;	//顶点数, 边数
}GraphAdjList;

//建立无向图的邻接表表示;
Status CreateALGraph(GraphAdjList *G)
{
	int i, j, k;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d,%d", &G->numNodes, &G->numEdges);
	for(i=0; i<G->numNodes; i++)		//建立顶点表
	{
		scanf(&G->adjList[i].data);		//输入顶点信息
		G->adjList[i].firstedge = NULL;	//置为空表
	}
	for(k=0; k<G->numEdges; k++)
	{
		printf("输入边(vi, vj)上顶点序号:\n");
		scanf("%d,%d", &i, &j);
		e = (EdgeNode *)malloc(sizeof(EdgeNode));	//生成边表结点
		e->adjvex = j;		//邻接序号为1
		e->next = G->adjList[i].firstedge;		//将e的指针指向当前顶点指向的结点
		G->adjList[i].firstedge = e;			//将当前顶点的指针指向e
		e = (EdgeNode *)malloc(sizeof(EdgeNode));	//生成边表结点
		e->adjvex = i;		//邻接序号为1
		e->next = G->adjList[j].firstedge;		//将e的指针指向当前顶点指向的结点
		G->adjList[j].firstedge = e;			//将当前顶点的指针指向e
	}
	return OK;
}

int main(void)
{
	GraphAdjList G;
	CreateALGraph(&G);
	
	return 0;
}
