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

typedef int Patharc[MAXVEX][MAXVEX];				//存储最短路径下标
typedef int ShortPathTable[MAXVEX][MAXVEX];	//存储到各点最短路径的权值和

Status CreateMGraph(MGraph *G)
{
	int i, j;
	G->numVertexes = 9;
	G->numEdges = 16;
	
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

//弗洛伊德Floyd算法求网图G中各顶点v到其余顶点w的最短路径P[v][w]及带权长度D[v][w];
Status ShortestPath_Floyd(MGraph G, Patharc *P, ShortPathTable *D)
{
	int v, w, k;
	for(v=0; v<G.numVertexes; ++v)
	{
		for(w=0; w<G.numVertexes; ++w)
		{
			(*D)[v][w] = G.arc[v][w];
			(*P)[v][w] = w;
		}
	}
	for(k=0; k<G.numVertexes; ++k)
	{
		for(v=0; v<G.numVertexes; ++v)
		{
			for(w=0; w<G.numVertexes; ++w)
			{
				if((*D)[v][w] > (*D)[v][k]+(*D)[k][w])
				{	//若经过下标为k的顶点的路径比原两点间路径更短
					(*D)[v][w] = (*D)[v][k]+(*D)[k][w];	//将当前两点间的权值设为更小1个
					(*P)[v][w] = (*P)[v][k];			//路径设置为经过下标为k的顶点
				}
			}
		}
	}
	return OK;
}

int main(void)
{
	int v, w, k;
	MGraph G;
	Patharc P;
	ShortPathTable D;
	
	CreateMGraph(&G);
	ShortestPath_Floyd(G, &P, &D);
	printf("各顶点间最短路径如下: \n");
	for(v=0; v<G.numVertexes; ++v)
	{
		for(w=v+1; w<G.numVertexes; w++)
		{
			printf("v%d-v%d weight: %d ", v, w, D[v][w]);
			k = P[v][w];				//获得第1个路径顶点下标
			printf(" path: %d", v);		//打印源点
			while(k!=w)			//如果路径顶点下标不是终点
			{
				printf(" -> %d", k);	//打印路径顶点
				k = P[k][w];			//获得下一个路径顶点下标
			}
			printf(" -> %d\n", w);		//打印终点
		}
		printf("\n");
	}
	printf("最短路径D\n");
	for(v=0; v<G.numVertexes; ++v)
	{
		for(w=0; w<G.numVertexes; ++w)
			printf("%d\t", D[v][w]);
		printf("\n");
	}
	printf("最短路径P\n");
	for(v=0; v<G.numVertexes; ++v)
	{
		for(w=0; w<G.numVertexes; ++w)
			printf("%d ", P[v][w]);
		printf("\n");
	}
	return 0;
}
