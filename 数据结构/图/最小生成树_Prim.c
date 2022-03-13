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

//普里姆Prim算法生成最小生成数;
Status MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MAXVEX];		//保存相关的顶点下标
	int lowcost[MAXVEX];	//保存顶点间边的权值
	lowcost[0] = 0;		//初始化第一个权值为0即v0加入生成树
	adjvex[0] = 0;		//初始化第一个顶点下标为0
	
	for(i=1; i<G.numVertexes; i++)	//循环下标非零的全部顶点
	{
		lowcost[i] = G.arc[0][i];	//将v0顶点与其边的权值存储
		adjvex[i] = 0;
	}
	for(i=1; i<G.numVertexes; i++)
	{
		min = GRAPH_INFINITY;		//初始化最小权值为∞
		j = 1;
		k = 0;
		while(j < G.numVertexes)
		{
			if(lowcost[j]!=0 && lowcost[j]<min)		//权值比较
			{
				min = lowcost[j];
				k = j;		//将当前最小值的下标存入k
			}
			j++;
		}
		printf("(%d, %d)\n", adjvex[k], k);			//打印当前顶点边中权值最小的边
		lowcost[k] = 0;		//将当前顶点的权值设置为0, 表示已完成任务
		for(j=1; j<G.numVertexes; j++)
		{	//下标为k的顶点各边的权值小于此前这些顶点未被加入生成树权值
			if(lowcost[j]!=0 && G.arc[k][j]<lowcost[j])
			{
				lowcost[j] = G.arc[k][j];
				adjvex[j] = k;
			}
		}
	}
	return OK;
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
	
	return 0;
}
