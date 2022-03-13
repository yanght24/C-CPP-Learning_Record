#include<stdio.h>    
#include<stdlib.h>   
#include<math.h>  
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 9		//存储空间初始分配量
#define MAXEDGE 15
#define MAXVEX 9

typedef int Status;			//函数结果状态代码
typedef char VertexType;	//顶点类型
typedef int EdgeType;		//权值类型
typedef int Boolean;		//判断是否已被访问

typedef struct
{
	VertexType vexs[MAXSIZE];		//顶点表
	EdgeType arc[MAXSIZE][MAXSIZE];	//邻接矩阵, 可看作边表
	int numVertexes, numEdges;		//顶点数, 边数
}MGraph;

//邻接表结构;
typedef struct EdgeNode		//边表结点
{
	int adjvex;			//邻接点域, 存储该结点对应的下标
	int weight;			//存储权值
	struct EdgeNode *next;	//链域, 指向下一个邻接点
}EdgeNode;

typedef struct VertexNode	//顶点表结点
{
	int in;				//顶点入度
	char data;			//顶点域, 存储顶点信息
	struct EdgeNode *firstedge;		//边表头结点
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjlist;
	int numVertexes, numEdges;
}graphAdjList, *GraphAdjList;

//循环队列的顺序存储结构;
typedef struct
{
	int data[MAXSIZE];
	int front;
	int rear;
}Queue;

//初始化1个空队列Q;
Status InitQueue(Queue *Q)
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//队列Q为空, 返回true, 否则返回false;
Status QueueEmpty(Queue Q)
{
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}

//队列未满, 则插入e为新的队尾元素;
Status EnQueue(Queue *Q, int e)
{
	if((Q->rear+1)%MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear+1)%MAXSIZE;
	
	return OK;
}

//队列不空, 则删除队头元素并用e返回;
Status DeQueue(Queue *Q, int *e)
{
	if(Q->front==Q->rear)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	
	return OK;
}

//建图;
Status CreateMGraph(MGraph *G)
{
	int i, j;
	G->numVertexes=9;
	G->numEdges=15;
	
	G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';
	
	for(i=0; i<G->numVertexes; i++)
	{
		for(j=0; j<G->numVertexes; j++)
		{
			G->arc[i][j] = 0;
		}
	}
	G->arc[0][1]=1;
	G->arc[0][5]=1;
	G->arc[1][2]=1; 
	G->arc[1][8]=1; 
	G->arc[1][6]=1; 
	G->arc[2][3]=1; 
	G->arc[2][8]=1; 
	G->arc[3][4]=1;
	G->arc[3][7]=1;
	G->arc[3][6]=1;
	G->arc[3][8]=1;
	G->arc[4][5]=1;
	G->arc[4][7]=1;
	G->arc[5][6]=1; 
	G->arc[6][7]=1; 
	for(i=0; i<G->numVertexes; i++)
	{
		for(j=i; j<G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
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
		(*GL)->adjlist[i].in = 0;
		(*GL)->adjlist[i].data = G.vexs[i];
		(*GL)->adjlist[i].firstedge = NULL;		//边表置为空表
	}
	for(i=0; i<G.numVertexes; i++)		//建立边表
	{
		for(j=G.numVertexes-1; j>=0; j--)
		{
			if(G.arc[i][j]==1)
			{
				e = (EdgeNode *)malloc(sizeof(EdgeNode));
				if(i==0 && j==8)
					e->adjvex = 6;
				else if(i==1 && j==6)
					e->adjvex = 8;
				else
					e->adjvex = j;		//邻接序号为j
				e->next = (*GL)->adjlist[i].firstedge;
				(*GL)->adjlist[i].firstedge = e;
				(*GL)->adjlist[j].in++;
			}
		}
	}
	return OK;
}

//访问标志的数组;
Boolean visited[MAXVEX];

//深度优化递归算法;
void DFS(GraphAdjList GL, int i)
{
	EdgeNode *p;
	visited[i] = TRUE;
	printf("%c ", GL->adjlist[i].data);
	p = GL->adjlist[i].firstedge;
	while(p)
	{
		if(!visited[p->adjvex])
			DFS(GL, p->adjvex);
		p = p->next;
	}
}

//深度遍历;
void DFSTraverse(GraphAdjList GL)
{
	int i;
	for(i=0; i<GL->numVertexes; i++)
		visited[i] = FALSE;
	for(i=0; i<GL->numVertexes; i++)
		if(!visited[i])
			DFS(GL, i);
}

//广度遍历;
void BFSTraverse(GraphAdjList GL)
{
	int i;
	EdgeNode *p;
	Queue Q;
	for(i=0; i<GL->numVertexes; i++)
		visited[i] = FALSE;
	InitQueue(&Q);
	for(i=0; i<GL->numVertexes; i++)
	{
		if(!visited[i])
		{
			visited[i] = TRUE;
			printf("%c ", GL->adjlist[i].data);
			EnQueue(&Q, i);
			while(!QueueEmpty(Q))
			{
				DeQueue(&Q, &i);
				p = GL->adjlist[i].firstedge;
				while(p)
				{
					if(!visited[p->adjvex])
					{
						visited[p->adjvex] = TRUE;
						printf("%c ", GL->adjlist[p->adjvex].data);
						EnQueue(&Q, p->adjvex);
					}
					p = p->next;
				}
			}
		}
	}
}

int main(void)
{    
	MGraph G;  
	GraphAdjList GL;    
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	
	printf("\n深度遍历:");
	DFSTraverse(GL);
	printf("\n广度遍历:");
	BFSTraverse(GL);
	return 0;
}
