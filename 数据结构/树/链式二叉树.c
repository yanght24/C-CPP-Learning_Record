//用1个数据域和2个指针域组成二叉链表
//可以再增加1个指向其双亲的指针域, 构成三叉链表

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 			//存储空间初始分配量

typedef int Status;			//函数结果状态代码
typedef char TElemType;		//树结点数据结构类型

TElemType Nil=' ';			//字符型以空格符为空

//构造二叉树;
int treeIndex = 1;
typedef char String[24];	//0号单元存储根结点
String str;

Status StrAssign(String T, char *chars)
{
	int i;
	if(strlen(chars) > MAXSIZE)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for(i=1; i<=T[0]; i++)
			T[i] = *(chars+i-1);
		return OK;
	}
}

Status visit(TElemType e)
{
	printf("%c ",e);
	return OK;
}

//结点结构;
typedef struct BiTNode
{
	TElemType data;		//结点数据
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode, *BiTree;

//构造空二叉树;
Status InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}

#define ClearBiTree InitBiTree
//顺序存储结果中, 两函数完全一样

//若二叉树存在, 则销毁;
Status DestoryBiTree(BiTree *T)
{
	if(*T)
	{
		if((*T)->lchild)	//有左孩子
			DestoryBiTree(&(*T)->lchild);	//销毁左孩子子树
		if((*T)->rchild)	//有右孩子
			DestoryBiTree(&(*T)->rchild);	//销毁右孩子子树
		free(*T);			//释放根结点
		*T = NULL;			//空指针赋0
	}
	return OK;
}

//按definition中给出的树的定义来构造树;
Status CreateBiTree(BiTree *T)
{
	TElemType ch;
	ch = str[treeIndex++];
	if(ch=='#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(!*T)
			return ERROR;
		(*T)->data = ch;	//生成根结点
		CreateBiTree(&(*T)->lchild);	//生成左子树
		CreateBiTree(&(*T)->rchild);	//生成右子树
	}
	return OK;
}

//若树T为空树, 返回true, 否则返回false;
Status EmptyBiTree(BiTree T)
{
	if(T)
		return FALSE;
	else
		return TRUE;
}

//返回树T的深度;
Status DepthBiTree(BiTree T)
{
	int i, j;
	if(!T)
		return ERROR;
	if(T->lchild)
		i = DepthBiTree(T->lchild);
	else
		i = 0;
	if(T->rchild)
		i = DepthBiTree(T->rchild);
	else
		j = 0;
	return i>j?i+1:j+1;
}

//返回树T的根结点;
Status Root(BiTree T)
{
	if(EmptyBiTree(T))
		return Nil;
	else
		return T->data;
}

//返回cur_e结点的值;
TElemType Value(BiTree p)
{
	return p->data;
}

//给结点cur_e赋值为value;
	Status Assign(BiTree p, TElemType value)
{
	p->data = value;
}

//前序递归遍历, 根---左---右;
Status PreOrderTraverse(BiTree T)
{
	if(T==NULL)
		return ERROR;
	printf("%c", T->data);		//显示结点数据, 可更改为其他对结点的操作
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

//中序递归遍历, 左---根---右;
Status InOrderTraverse(BiTree T)
{
	if(T==NULL)
		return ERROR;
	InOrderTraverse(T->lchild);
	printf("%c", T->data);
	InOrderTraverse(T->rchild);
}

//后序递归遍历, 左---右---根;
Status PostOrderTraverse(BiTree T)
{
	if(T==NULL)
		return ERROR;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c", T->data);
}

int main(void)
{
	int i;
	BiTree T;
	TElemType e;
	
	InitBiTree(&T);
	StrAssign(str, "ABDH#K###E##CFI###G#J##");
	CreateBiTree(&T);
	printf("构造一个二叉树, 是否为空: %d (1:是 0:否)\n", EmptyBiTree(T));
	printf("树的深度为: %d\n", DepthBiTree(T));
	e = Root(T);
	printf("二叉树的根为: %c\n", e);
	printf("\n前序遍历二叉树:");
	PreOrderTraverse(T);
	printf("\n中序遍历二叉树:");
	InOrderTraverse(T);
	printf("\n后序遍历二叉树:");
	PostOrderTraverse(T);
	ClearBiTree(&T);
	printf("\n清空二叉树后, 是否为空: %d (1:是 0:否)\n", EmptyBiTree(T));
	printf("此时, 树的深度为: %d\n", DepthBiTree(T));
	i = Root(T);
	if(!i)
		printf("树空，无根\n");
	return 0;
}
