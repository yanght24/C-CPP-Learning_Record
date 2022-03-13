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
	EdgeType arc[MAXSIZE][MAXSIZE];	//邻接矩阵
	int numVertexes, numEdges;		//顶点数, 边数
}MGraph;

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
	if(Q.front == Q.rear)	//为空标志
		return TRUE;
	else
		return FALSE;
}

//队列未满, 则插入e为新的队尾元素;
Status EnQueue(Queue *Q, int e)
{
	if((Q->rear+1)%MAXSIZE == Q->front)		//为满标志
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear+1)%MAXSIZE;			//若最后则转至头部
	
	return OK;
}

//队列不空, 则删除队头元素并用e返回;
Status DeQueue(Queue *Q, int *e)
{
	if(Q->front == Q->rear)		//为空标志
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;		//若最后则转至头部
	
	return OK;
}

//建图;
Status CreateMGraph(MGraph *G)
{
	int i, j;
	G->numVertexes = 9;
	G->numEdges = 15;
	
	G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';
	
	for(i=0; i<G->numVertexes; i++)		//初始化图
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

//访问标志的数组;
Boolean visited[MAXVEX];

//深度优化递归算法;
void DFS(MGraph G, int i)
{
	int j;
	visited[i] = TRUE;
	printf("%c ", G.vexs[i]);	//打印顶点或进行其他操作
	for(j=0; j<G.numVertexes; j++)
		if(G.arc[i][j]==1 && !visited[j])
			DFS(G, j);
}

//深度遍历;
void DFSTraverse(MGraph G)
{
	int i;
	for(i=0; i<G.numVertexes; i++)
		visited[i] = FALSE;		//初始化所有顶点都是未被访问
	for(i=0; i<G.numVertexes; i++)
		if(!visited[i])			//对未访问的顶点调用DFS, 若是连通图, 只执行一次
			DFS(G, i);
}

//广度遍历;
void BFSTraverse(MGraph G)
{
	int i, j;
	Queue Q;
	for(i=0; i<G.numVertexes; i++)
		visited[i] = FALSE;
	InitQueue(&Q);			//初始化1辅助用的队列
	for(i=0; i<G.numVertexes; i++)		//对每一个顶点做循环
	{
		if(!visited[i])		//未被访问就进行处理
		{
			visited[i] = TRUE;
			printf("%c ", G.vexs[i]);	//打印顶点/其他操作
			EnQueue(&Q, i);			//将此顶点入队列
			while(!QueueEmpty(Q))		//若当前队列非空
			{
				DeQueue(&Q, &i);		//将队首元素出队列, 赋给i
				for(j=0; j<G.numVertexes; j++)
				{
					if(G.arc[i][j]==1 && !visited[j])
					{
						visited[j] = TRUE;
						printf("%c ", G.vexs[j]);
						EnQueue(&Q, j);
					}
				}
			}
		}
	}
	
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	printf("\n深度遍历: ");
	DFSTraverse(G);
	printf("\n广度遍历: ");
	BFSTraverse(G);
	
	return 0;
}
