#include<stdio.h>    
#include<stdlib.h>   
#include<math.h>  
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 20
#define MAXEDGE 20
#define GRAPH_INFINITY 65535	//用来表示∞

typedef int Status;
typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;			//边集数组结构

Status CreateMGraph(MGraph *G)
{
	int i, j;
	G->numVertexes = 9;
	G->numEdges = 15;
	
	for(i=0; i<G->numVertexes; i++)
	{
		for(j=0; j<G->numVertexes; j++)
		{
			if(i==j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = GRAPH_INFINITY;
		}
	}
	G->arc[0][1]=10;
	G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19;
	for(i=0; i<G->numVertexes; i++)
	{
		for(j=i; j<G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
	return OK;
}

//交换权值, 以及头和尾;
Status Swap(Edge *edges, int i, int j)
{
	int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
	return OK;
}

//权值排序;
Status Sort(Edge edges[], MGraph *G)
{
	int i, j;
	for(i=0; i<G->numEdges; i++)
	{
		for(j=i+1; j<G->numEdges; j++)
		{
			if(edges[i].weight > edges[j].weight)
			{
				Swap(edges, i, j);
			}
		}
	}
	printf("权值排序后为: \n");
	for(i=0; i<G->numEdges; i++)
		printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
	return OK;
}

//查找连线顶点的尾部下标;
Status Find(int *parent, int f)
{
	while(parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}

//克鲁斯卡尔Kruskal算法生成最小生成树;
Status MiniSpanTree_Kruskal(MGraph G)
{
	int i, j, n, m;
	int k =0;
	int parent[MAXVEX];		//用来判断边与边是否形成环路
	Edge edges[MAXEDGE];	//边集数组
	
	for(i=0; i<G.numVertexes-1; i++)	//构建边集数组并排序
	{
		for(j=i+1; j<G.numVertexes; j++)
		{
			if(G.arc[i][j]<GRAPH_INFINITY)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}
	Sort(edges, &G);
	for(i=0; i<G.numVertexes; i++)
		parent[i] = 0;
	printf("打印最小生成树: \n");
	for(i=0; i<G.numEdges; i++)		//循环每一条边
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		if(n!=m)		//未形成环路
		{	//将此边的结尾顶点放入下标为起点的parent中, 表示此顶点已在生成树集合中
			parent[n] = m;
			printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
	return OK;
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
	
	return 0;
}
