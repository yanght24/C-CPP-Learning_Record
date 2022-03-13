//二叉链表+指向前驱后继的指针(线索)构成线索链表, 即将二叉树转变成双向链表
//二叉树以某种次序遍历使其变为线索二叉树的过程称为线索化, 即在遍历的过程中修改空指针
//空指针域中的lchild指向前驱, rchild指向后继
//需加上区分标志tag, 以区分孩子和前驱后继

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
typedef enum {Link, Thread} PointerTag;
//Link==0表示指向左右孩子的指针
//Thread==1表示指向前驱后继的线索
TElemType Nil='#';			//字符型以#为空

typedef struct BiThrNode	//二叉线索存储结点结构
{
	TElemType data;		//结点数据
	struct BiThrNode *lchild, *rchild;		//左右孩子指针
	PointerTag LTag;	//为0指向左孩子, 为1指向前驱
	PointerTag RTag;	//为0指向右孩子, 为1指向后继
}BiThrNode, *BiThrTree;

Status visit(TElemType e)
{
	printf("%c ",e);
	return OK;
}

//按前序输入二叉线索树中结点的值,构造二叉线索树;
Status CreateBiThrTree(BiThrTree *T)
{
	TElemType h;
	scanf("%c", &h);
	if(h==Nil)
		*T = NULL;
	else
	{
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if(!*T)
			return ERROR;
		(*T)->data = h;		//生成根结点
		CreateBiThrTree(&(*T)->lchild);		//构造左子树
		if((*T)->lchild)	//有左孩子
			(*T)->LTag = Link;
		CreateBiThrTree(&(*T)->rchild);		//构造右子树
		if((*T)->rchild)	//有右孩子
			(*T)->RTag = Link;
	}
	return OK;
}

//全局变量, 始终指向刚刚访问过的结点;
BiThrTree pre;

//中序遍历进行中序线索化;
Status InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);		//递归左子树线索化
		if(!p->lchild)		//无左孩子
		{
			p->LTag = Thread;		//前驱线索
			p->lchild = pre;		//左孩子指向前驱
		}
		if(!pre->rchild)	//前驱无右孩子
		{
			pre->RTag = Thread;		//后继线索
			pre->rchild = p;		//前驱右孩子指针指向后继(当前结点p)
		}
		pre = p;			//保持pre指向p的前驱
		InThreading(p->rchild);		//递归右子树线索化
	}
	return OK;
}

//中序遍历二叉树T,并将其中序线索化,Thrt指向头结点;
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt)
		return ERROR;
	(*Thrt)->LTag = Link;		//构造头结点
	(*Thrt)->RTag = Thread;
	(*Thrt)->rchild = (*Thrt);	//右指针回指
	if(!T)		//若二叉树为空, 则左指针回指
		(*Thrt)->lchild = *Thrt;
	else
	{
		(*Thrt)->lchild = T;
		pre = (*Thrt);
		InThreading(T);		//中序遍历进行中序线索化
		pre->rchild = *Thrt;
		pre->RTag = Thread;		//最后1个结点线索化
		(*Thrt)->rchild = pre;
	}
	return OK;
}

//中序遍历二叉线索树T(头结点)的非递归算法;
Status InOrderTraverse_Thr(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild;		//p指向根结点
	while(p!=T)			//空树/遍历结束时, p==T
	{
		while(p->LTag == Link)
			p = p->lchild;
		if(!visit(p->data))		//访问其左子树为空的结点
			return ERROR;
		while(p->RTag==Thread && p->rchild!=T)
		{
			p = p->rchild;
			visit(p->data);		//访问后继结点
		}
		p = p->rchild;
	}
	return OK;
}

int main(void)
{
	BiThrTree H,T;
	printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
	CreateBiThrTree(&T); 		//按前序产生二叉树
	InOrderThreading(&H,T); 	//中序遍历,并中序线索化二叉树
	printf("中序遍历(输出)二叉线索树:\n");
	InOrderTraverse_Thr(H); 	//中序遍历(输出)二叉线索树
	printf("\n");
	return 0;
}









