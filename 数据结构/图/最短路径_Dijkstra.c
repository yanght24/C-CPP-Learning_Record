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
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef int Patharc[MAXVEX];		//存储最短路径下标
typedef int ShortPathTable[MAXVEX];	//存储到各点最短路径的权值和

Status CreateMGraph(MGraph *G)
{
	int i, j;
	G->numVertexes = 9;
	G->numEdges = 15;
	
	for(i=0; i<G->numVertexes; i++)
		G->vexs[i] = i;
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
	G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 
	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;
	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;
	G->arc[7][8]=4;
	for(i=0; i<G->numVertexes; i++)
	{
		for(j=i; j<G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}
	return OK;
}

//迪杰斯特拉Dijkstra算法求有向网G的v0到其余顶点v的最短路径P[v]及带权长度D[v];
//P[v]的值为前驱顶点下标, D[v]为v0到v的最短路径长度和;
Status ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D)
{
	int v, w, k, min;
	int final[MAXVEX];		//final[j]=1表示求得顶点v0至vw的最短路径
	for(v=0; v<G.numVertexes; v++)
	{
		final[v] = 0;		//全部顶点初始化为未知最短路径状态
		(*D)[v] = G.arc[v0][v];		//将与v0有连线的顶点加上权值
		(*P)[v] = -1;		//初始化路径数值P为1
	}
	(*D)[v0] = 0;			//v0至v0路径为0
	final[v0] = 1;			//v0至v0不用求
	
	for(v=1; v<G.numVertexes; v++)		//循环, 每次求得v0到v顶点的最短路径
	{
		min = GRAPH_INFINITY;			//初始化最短距离
		for(w=0; w<G.numVertexes; w++)
		{
			if(!final[w] && (*D)[w]<min)
			{
				k = w;
				min = (*D)[w];			//w顶点离v0更近
			}
		}
		final[k] = 1;		//将目前找到的最近的顶点置为1
		for(w=0; w<G.numVertexes; w++)	//修正当前最短路径及距离
		{	//经过v顶点的路径比现在这条路径更短:
			if(!final[w] && (min+G.arc[k][w]<(*D)[w]))
			{
				(*D)[w] = min+G.arc[k][w];
				(*P)[w] = k;
			}
		}
	}
	return OK;
}

int main(void)
{
	int i, j, v0;
	MGraph G;
	Patharc P;
	ShortPathTable D;
	v0 = 0;
	
	CreateMGraph(&G);
	ShortestPath_Dijkstra(G, v0, &P, &D);
	printf("最短路径倒叙如下: \n");
	for(i=1; i<G.numVertexes; ++i)
	{
		printf("v%d - v%d : ", v0, i);
		j = i;
		while(P[j]!=-1)
		{
			printf("%d ", P[j]);
			j = P[j];
		}
		printf("\n");
	}
	printf("\n原点到各顶点的最短路径长度为: \n");
	for(i=1; i<G.numVertexes; ++i)
		printf("v%d - v%d : %d \n", G.vexs[0], G.vexs[i], D[i]);
	return 0;
}
