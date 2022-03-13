//用1维数组存储二叉树的结点, 一般只用于完全二叉树
//并且结点的存储位置即数组下标能体现结点间的逻辑关系

#include<stdio.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 			//存储空间初始分配量
#define MAX_TREE_SIZE 100 		//二叉树的最大结点数

typedef int Status;			//函数结果状态代码
typedef int TElemType;		//树结点数据结构类型
typedef TElemType SqBiTree[MAX_TREE_SIZE];	//0号单元存储根结点

TElemType Nil = 0;			//整型以0为空

typedef struct		//定义结点位置
{
	int level;		//结点的层
	int order;		//本层序号
}Position;

Status visit(TElemType c)
{
	printf("%d ", c);
	return OK;
}

//构造空树T, T为固定数组, 故不需要&;
Status InitBiTree(SqBiTree T)
{
	int i;
	for(i=0; i<MAX_TREE_SIZE; i++)
		T[i] = Nil;		//初始值为空
	return OK;
}

#define ClearBiTree InitBiTree
//顺序存储结果中, 两函数完全一样

//按definition中给出的树的定义来构造树;
Status CreateBiTree(SqBiTree T)
{
	int i = 0;
	printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n", MAX_TREE_SIZE);
	while(i<10)
	{
		T[i] = i+1;
		if (i!=0 && T[(i+1)/2-1]==Nil && T[i]!=Nil)		//此结点非空无双亲且不是根结点
		{
			printf("出现无双亲的非根结点%d\n", T[i]);
			return ERROR;
		}
		i++;
	}
	while(i<MAX_TREE_SIZE)
	{
		T[i] = Nil;		//空值赋给T后面的结点
		i++;
	}
	return OK;
}

//若树T为空树, 返回true, 否则返回false;
Status EmptyBiTree(SqBiTree T)
{
	if (T[0] == Nil)
		return TRUE;
	else
		return FALSE;
}

//返回树T的深度;
Status DepthBiTree(SqBiTree T)
{
	int i, j=-1;
	for(i=MAX_TREE_SIZE-1; i>=0; i--)	//找到最后1个结点
		if (T[i] != Nil)
			break;
	i++;		//得到结点个数
	do{
		j++;
	}while(i>=pow(2, j));	
	return j;
}

//返回树T的根结点;
Status Root(SqBiTree T, TElemType *e)
{
	if (EmptyBiTree(T))
		return ERROR;
	else
	{
		*e = T[0];
		return OK;
	}
}

//返回cur_e结点的值;
TElemType Value(SqBiTree T, Position e)
{
	return T[(int)powl(2, e.level-1)+e.order-2];
	//二叉树的第i层至多2^(i-1)个结点, 等同于第i层第1个结点下标
	//然后order-2以得到结点对应的下标值
}

//给结点cur_e赋值为value;
Status Assign(SqBiTree T, Position e, TElemType value)
{
	int i = (int)powl(2, e.level-1)+e.order-2;		//得到结点下标值
	if(value!=Nil && T[(i+1)/2-1]==Nil)			//给叶子赋非空值但双亲为空
		return ERROR;
	else if(value==Nil && (T[i*2+1]!=Nil || T[i*2+2]!=Nil))	//给双亲赋空值但有叶子
		return ERROR;
	T[i] = value;
	
	return OK;
}

//若cur_e为非根结点, 则返回其双亲;
TElemType Parent(SqBiTree T, TElemType e)
{
	int i;
	if(T[0] == Nil)		//空树
		return ERROR;
	for(i=1; i<=MAX_TREE_SIZE-1; i++)
		if(T[i] == e)	//找到e
			return T[(i+1)/2-1];
	return FALSE;		//没找到e
}

//返回e的左孩子;
TElemType LeftChild(SqBiTree T, TElemType e)
{
	int i;
	if(T[0] == Nil)
		return ERROR;
	for(i=1; i<=MAX_TREE_SIZE-1; i++)
		if(T[i] == e)
			return T[i*2+1];
	return FALSE;
}

//返回e的右孩子;
TElemType RightChild(SqBiTree T, TElemType e)
{
	int i;
	if(T[0] == Nil)
		return ERROR;
	for(i=1; i<=MAX_TREE_SIZE-1; i++)
		if(T[i] == e)
			return T[i*2+2];
	return FALSE;
}

//返回e的左兄弟;
TElemType LeftSibling(SqBiTree T, TElemType e)
{
	int i;
	if(T[0] == Nil)
		return ERROR;
	for(i=1; i<=MAX_TREE_SIZE-1; i++)
		if(T[i]==e && i%2==0)		//找到e且其序号为偶数(为右孩子)
			return T[i-1];
	return FALSE;
}

//返回e的右兄弟;
TElemType RightSibling(SqBiTree T, TElemType e)
{
	int i;
	if(T[0] == Nil)
		return ERROR;
	for(i=1; i<=MAX_TREE_SIZE-1; i++)
		if(T[i]==e && i%2)		//找到e且其序号为奇数(为左孩子)
			return T[i+1];
	return FALSE;
}

//PreOrderTraverse()调用
void PreTraverse(SqBiTree T, int e)
{
	visit(T[e]);
	if(T[2*e+1] != Nil)		//左子树非空
		PreTraverse(T, 2*e+1);
	if(T[2*e+2] != Nil)		//右子树非空
		PreTraverse(T, 2*e+2);
}

//前序遍历, 根---左---右;
Status PreOrderTraverse(SqBiTree T)
{
	if(!EmptyBiTree(T))		//树非空
		PreTraverse(T, 0);
	printf("\n");
	return OK;
}

//InOrderTraverse()调用
void InTraverse(SqBiTree T, int e)
{
	if(T[2*e+1] != Nil)		//左子树非空
		InTraverse(T, 2*e+1);
	visit(T[e]);			//先遍历根结点的左子树
	if(T[2*e+2] != Nil)		//右子树非空
		InTraverse(T, 2*e+2);
}

//中序遍历, 左---根---右;
Status InOrderTraverse(SqBiTree T)
{
	if(!EmptyBiTree(T))		//树非空
		InTraverse(T, 0);
	printf("\n");
	return OK;
}

//PostOrderTraverse()调用
void PostTraverse(SqBiTree T, int e)
{
	if(T[2*e+1] != Nil)		//左子树非空
		PostTraverse(T, 2*e+1);
	if(T[2*e+2] != Nil)		//右子树非空
		PostTraverse(T, 2*e+2);
	visit(T[e]);			//
}

//后序遍历, 左---右---根;
Status PostOrderTraverse(SqBiTree T)
{
	if(!EmptyBiTree(T))		//树非空
		PostTraverse(T, 0);
	printf("\n");
	return OK;
}

//层序遍历, 自根结点开始从上而下逐层遍历;
Status LevelOrderTraverse(SqBiTree T)
{
	int i = MAX_TREE_SIZE-1, j;
	while(T[i] == Nil)
		i--;				//找到最后一个非空结点
	for(j=0; j<=i; j++)
		if(T[j] != Nil)		//只遍历非空结点
			visit(T[j]);
	printf("\n");
	return OK;
}

//逐层, 按本层序号输出二叉树;
Status Print(SqBiTree T)
{
	int j, k;
	Position p;
	TElemType e;
	for(j=1; j<=DepthBiTree(T); j++)
	{
		printf("第%d层: ", j);
		for(k=1; k<=powl(2, j-1); k++)
		{
			p.level = j;
			p.order = k;
			e = Value(T, p);
			if(e != Nil)
				printf("第%d个: %d ", k, e);
		}
		printf("\n");
	}
	return OK;
}

int main(void)
{
	Status i;
	Position p;
	TElemType e;
	SqBiTree T;
	
	CreateBiTree(T);
	printf("构造一个二叉树, 是否为空: %d (1:是 0:否)\n", EmptyBiTree(T));
	printf("树的深度为: %d\n", DepthBiTree(T));
	i = Root(T, &e);
	if(i)
		printf("二叉树的根为: %d\n", e);
	else
		printf("树空, 无根\n");
	printf("层序遍历二叉树: \n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树: \n");
	PreOrderTraverse(T);
	printf("中序遍历二叉树: \n");
	InOrderTraverse(T);
	printf("后序遍历二叉树: \n");
	PostOrderTraverse(T);
	printf("修改第%d层, 本层序号为%d的结点", 3, 2);
	p.level = 3;
	p.order = 2;
	e = Value(T, p);
	printf("待修改结点原值为: %d and输入新值: ", e);
	scanf("%d", &e);
	Assign(T, p, e);
	printf("此时, 层序遍历二叉树: \n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树: \n");
	PreOrderTraverse(T);
	printf("\n");
	
	printf("结点%d的双亲为%d\n", e, Parent(T, e));
	printf("左孩子为: %d, 右孩子为: %d\n", LeftChild(T, e), RightChild(T, e));
	printf("左兄弟为: %d, 右兄弟为: %d\n", LeftSibling(T, e), RightSibling(T, e));
	ClearBiTree(T);
	printf("清空二叉树后, 是否为空: %d (1:是 0:否)\n", EmptyBiTree(T));
	printf("此时, 树的深度为: %d\n", DepthBiTree(T));
	i = Root(T, &e);
	if(i)
		printf("二叉树的根为: %d\n", e);
	else
		printf("树空, 无根\n");
	
	return 0;
}










