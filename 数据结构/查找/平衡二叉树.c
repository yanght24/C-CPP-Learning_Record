//二叉排序树的一种, 其中每个结点的左子树和右子树的高度差至多等于1
//左子树高度 - 右子树高度 = 平衡因子BF (只能为-1, 0, 1)
//距离插入结点最近的且|平衡因子|>1的结点为根的子树, 称为最小不平衡子树
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 	//存储空间初始分配量

#define LH +1	//左高
#define EH 0	//等高
#define RH -1	//右高
typedef int Status;

typedef struct BiTNode	//结点结构
{
	int data;
	int bf;		//结点平衡因子
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//对以P为根的二叉排序树作右旋处理 (平衡因子BF大于1时);
//处理后P指向新的树根结点, 即处理前的左子树的根结点
void R_Rotate(BiTree *P)
{
	BiTree L;
	L = (*P)->lchild;		//L指向P的左子树根结点
	(*P)->lchild = L->rchild;	//L的右子树接挂为P的左子树
	L->rchild = (*P);		
	*P = L;					//P指向新的根结点
}

//对以P为根的二叉排序树作左旋处理 (平衡因子BF小于-1时);
//处理后P指向新的树根结点, 即处理前的右子树的根结点
void L_Rotate(BiTree *P)
{
	BiTree R;
	R = (*P)->rchild;		//R指向P的右子树根结点
	(*P)->rchild = R->lchild;	//R的左子树接挂为P的右子树
	R->lchild = (*P);
	*P = R;					//P指向新的根结点
}

//对以指针T所指结点为根的二叉树作左平衡旋转处理;
void LeftBalance(BiTree *T)
{
	BiTree L, Lr;
	L = (*T)->lchild;		//L指向T的左子树根结点
	switch(L->bf)
	{	//检查T的左子树的平衡度, 并作相应处理
		case LH:			//新结点插在T的左孩子的左子树上, 作右旋处理
			(*T)->bf = L->bf = EH;
			R_Rotate(T);
			break;
		case RH:			//新结点插在T的左孩子的右子树上, 作双旋处理
			Lr = L->rchild;	//Lr指向T的左孩子的右子树根
			switch(Lr->bf)
			{	//修改T及其左子树的平衡因子
				case LH:(*T)->bf = RH;
						L->bf = EH;
						break;
				case EH:(*T)->bf = EH;
						L->bf = EH;
						break;
				case RH:(*T)->bf = EH;
						L->bf = LH;
						break;
			}
			Lr->bf = EH;
			L_Rotate(&(*T)->lchild);	//对左子树作左旋平衡处理
			R_Rotate(T);				//对T作右旋平衡处理
	}
}

//对以指针T所指结点为根的二叉树作左平衡旋转处理;
void RightBalance(BiTree *T)
{
	BiTree R, Rl;
	R = (*T)->lchild;		//R指向T的右子树根结点
	switch(R->bf)
	{	//检查T的右子树的平衡度, 并作相应处理
		case LH:			//新结点插在T的右孩子的右子树上, 作左旋处理
			(*T)->bf = R->bf = EH;
			L_Rotate(T);
			break;
		case RH:			//新结点插在T的左孩子的右子树上, 作双旋处理
			Rl = R->lchild;	//Rl指向T的右孩子的左子树根
			switch(Rl->bf)
			{	//修改T及其右子树的平衡因子
				case RH:(*T)->bf = LH;
						R->bf = EH;
						break;
				case EH:(*T)->bf = EH;
						R->bf = EH;
						break;
				case LH:(*T)->bf = EH;
						R->bf = RH;
						break;
			}
			Rl->bf = EH;
			R_Rotate(&(*T)->rchild);	//对右子树作右旋平衡处理
			L_Rotate(T);				//对T作左旋平衡处理
	}
}

//若平衡的二叉排序树T中不存在和e有相同关键字的结点, 则插入e为数据元素的新结点;
//若插入后失衡, 则作平衡选择处理, 布尔变量taller反映T是否长高;
Status InsertAVL(BiTree *T, int e, Status *taller)
{
	if(!*T)
	{	//插入新结点, taller设置为TRUE
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		if(e==(*T)->data)
		{	//已存在相同结点则不插入
			*taller = FALSE;
			return FALSE;
		}
		if(e<(*T)->data)
		{	//继续在T的左子树中进行搜索
			if(!InsertAVL(&(*T)->lchild, e, taller))	//未插入
				return FALSE;
			if(*taller)		//已插入到T的左子树中且左子树长高
				switch((*T)->bf)		//检查T的平衡度
				{
					case LH:LeftBalance(T);
							*taller = FALSE;
							break;			//原本左子树比右子树高, 需作左平衡处理
					case EH:(*T)->bf = LH;
							*taller = TRUE;
							break;			//原本左右子树等高, 插入后左子树长高
					case RH:(*T)->bf = EH;
							*taller = FALSE;
							break;			//原本右子树比左子树高, 插入后等高
				}
		}
		else
		{	//继续在T的右子树中进行搜索
			if(!InsertAVL(&(*T)->rchild, e, taller))	//未插入
				return FALSE;
			if(*taller)		//已插入到T的右子树中且右子树长高
				switch((*T)->bf)		//检查T的平衡度
				{
					case LH:(*T)->bf = EH;
							*taller = FALSE;
							break;			//原本左子树比右子树高, 插入后等高
					case EH:(*T)->bf = RH;
							*taller = TRUE;
							break;			//原本左右子树等高, 插入后右子树长高
					case RH:RightBalance(T);
							*taller = FALSE;
							break;			//原本右子树比左子树高, 需作右平衡处理
				}
		}
	}
	return TRUE;
}

int main(void)
{
	int i;
	int a[10] = {3,2,1,4,5,6,7,10,9,8};
	BiTree T = NULL;
	Status taller;
	for(i=0; i<10; i++)
	{
		InsertAVL(&T, a[i], &taller);
	}
	return 0;
}
