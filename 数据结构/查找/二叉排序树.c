//既为了提高插入删除效率, 又能够较高效地实现查找
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 	//存储空间初始分配量

typedef int Status;

typedef struct BiTNode	//结点结构
{
	int data;			//结点数据
	struct BiTNode *lchild, *rchild;	//左右孩子指针
}BiTNode, *BiTree;

//递归查找二叉排序树T中是否存在值key;
//指针f指向T的双亲, 初始调用值为NULL;
//指针p用来返回查找结果
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
	if(!T)
	{
		*p = f;
		return FALSE;
	}
	else if(key==T->data)
	{
		*p = T;
		return TRUE;
	}
	else if(key<T->data)
		return SearchBST(T->lchild, key, T, p);
	else
		return SearchBST(T->rchild, key, T, p);
}

//不存在值为key的数据元素时, 插入key并返回TURE;
Status InsertBST(BiTree *T, int key)
{
	BiTree p, s;
	if(!SearchBST(*T, key, NULL, &p))
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if(!p)
			*T = s;			//插入s为新的根结点
		else if(key<p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else		//树中已有与关键字相同的结点
		return FALSE;
}

//删除结点p并重接左/右子树;
Status Delete(BiTree *p)
{
	BiTree q, s;
	if((*p)->rchild==NULL)		//只需要重接左子树
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if((*p)->lchild==NULL)	//只需要重接右子树
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else		//左右均不为空
	{
		q = *p;
		s = (*p)->lchild;
		while(s->rchild)	//左子树的最右结点(找待删结点的前驱)
		{
			q = s;
			s = s->rchild;	
		}
		(*p)->data = s->data;	//s指向被删结点的直接前驱(将被删结点前驱的值取代被删结点的值)
		if(q!=*p)
			q->rchild = s->lchild;		//重接q的右子树
		else
			q->lchild = s->rchild;		//重接q的左子树
		free(s);
	}
	return OK;
}

//存在值为key的数据元素时, 删除该结点并返回TRUE;
Status DeleteBST(BiTree *T, int key)
{
	if(!*T)
		return FALSE;
	else
	{
		if(key==(*T)->data)
			return Delete(T);
		else if(key<(*T)->data)
			return DeleteBST(&(*T)->lchild, key);
		else
			return DeleteBST(&(*T)->rchild, key);
	}
}

int main(void)
{
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T = NULL;
	for(i=0; i<10; i++)
	{
		InsertBST(&T, a[i]);
	}
	DeleteBST(&T, 93);
	DeleteBST(&T, 47);
	
	return 0;
}









