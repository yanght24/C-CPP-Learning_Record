//用于内外存数据交互;
/*
B树每个结点的孩子数可多于2个, 且每个结点处可以存储多个元素;
是一种平衡的多路查找树, 结点最大的孩子数目称为B树的阶

B+树出现在分支结点中的元素会用作在该分支结点位置的中序后继者中再次列出;
每个叶子结点都会保存1个指向后1叶子结点的指针
*/
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 	//存储空间初始分配量
#define m 3			//B树的阶
#define N 17		//元素个数
#define MAX 5		//字符串最大长度+1

typedef int Status;

typedef struct BTNode
{
	int keynum;		//结点中关键字个数, 即结点大小
	struct BTNode *parent;		//指向双亲结点
	struct Node		//结点向量类型
	{
		int key;	//关键字向量
		struct BTNode *ptr;		//子树指针向量
		int recptr;	//记录指针向量
	}node[m+1];		//key, recptr的0号单元不用
}BTNode, *BTree;	//B树的结点和类型

typedef struct
{
	BTNode *pt;		//指向找到的结点
	int i;			//在结点中的关键字序号
	int tag;		//标志: 1:查找成功, 0:查找失败
}Result;			//B树的查找结果类型

//在p->node[1~keunum].key中查找i, 使得p->node[i].key≤K＜p->node[i+1].key;
int Search(BTree p, int K)
{
	int j, i=0;
	for(j=1; j<=p->keynum; j++)
		if(p->node[j].key<=K)
			i = j;
	return i;
}

//在m阶B树T上查找关键字K, 返回结果(pt, i, tag);
//没找到则将等于K的关键字插入在指针pt所指结点中第i和i+1个关键字之间
Result SearchBTree(BTree T, int K)
{
	BTree p =T, q = NULL;	//初始化, p指向待查结点, q指向p的双亲
	Status found = FALSE;
	int i = 0;
	Result r;
	while(p && !found)
	{
		i = Search(p, K);	//p->node[i].key≤K<p->node[i+1].key
		if(i>0 && p->node[i].key==K)	//找到
			found = TRUE;
		else
		{
			q = p;
			p = p->node[i].ptr;
		}
	}
	r.i = i;
	if(found)	//查找成功
	{
		r.pt = p;
		r.tag= 1;
	}
	else		//返回K的插入位置信息
	{
		r.pt = q;
		r.tag= 0;
	}
	return r;
}

//将r->key, r, ap分别插入到q->key[i+1], q->recptr[i+1], q->ptr[i+1]中;
void Insert(BTree *q, int i, int key, BTree ap)
{
	int j;
	for(j=(*q)->keynum; j>i; j--)		//空出(*q)->node[i+1]
		(*q)->node[j+1] = (*q)->node[j];
	(*q)->node[i+1].key = key;
	(*q)->node[i+1].ptr = ap;
	(*q)->node[i+1].recptr = key;
	(*q)->keynum++;
}

//将结点q分成2个结点, 前1半保留, 后1半移入新结点ap;
void Split(BTree *q, BTree *ap)
{
	int s=(m+1)/2, i;
	*ap = (BTree)malloc(sizeof(BTNode));
	(*ap)->node[0].ptr = (*q)->node[s].ptr;		//后1半移入ap
	for(i=s+1; i<=m; i++)
	{
		(*ap)->node[i-s] = (*q)->node[i];
		if((*ap)->node[i-s].ptr)
		   (*ap)->node[i-s].ptr->parent = *ap;
	}
	(*ap)->keynum = m-s;
	(*ap)->parent = (*q)->parent;
	(*q)->keynum = s-1;			//前1半保留, 修改keynum
}

//生成含信息(T, r, ap)的新的根结点&T, 原T和ap为子树指针;
void NewRoot(BTree *T, int key, BTree ap)
{
	BTree p;
	p = (BTree)malloc(sizeof(BTNode));
	p->node[0].ptr = *T;
	*T= p;
	if((*T)->node[0].ptr)
	   (*T)->node[0].ptr->parent = *T;
	(*T)->parent = NULL;
	(*T)->keynum = 1;
	(*T)->node[1].key = key;
	(*T)->node[1].recptr = key;
	(*T)->node[1].ptr = ap;
	if((*T)->node[1].ptr)
	   (*T)->node[1].ptr->parent = *T;
}

//在m阶B树T上结点*q的key[i]和key[i+1]之间插入关键字K的指针r;
//若结点过大, 则沿双亲链进行必要的结点分裂调整, 使T仍是m阶B树
void InsertBTree(BTree *T, int key, BTree q, int i)
{
	BTree ap = NULL;
	Status finished = FALSE;
	int s;
	int rx = key;
	while(q && !finished)
	{
		Insert(&q, i, rx, ap);	//将r->key, r, ap分别插入到q->key[i+1], q->recptr[i+1], q->ptr[i+1]中
		if(q->keynum<m)
			finished = TRUE;	//插入完成
		else
		{	//分裂结点*q
			s = (m+1)/2;
			rx= q->node[s].recptr;
			Split(&q, &ap);		//将q->key[s+1~m], q->ptr[s~m], q->recptr[s+1~m]移入新结点*ap
			q = q->parent;
			if(q)
				i = Search(q, key);		//在双亲结点*q中查找rx->key的插入位置
		}
	}
	if(!finished)		//T是空树(参数q初始值为NULL)或根结点已分裂为结点*q和*ap
		NewRoot(T, rx, ap);		//生成含信息(T, rx, ap)的新的根结点*T, 原T和ap为子树指针
}

void Print(BTNode c, int i)
{
	printf("(%d)", c.node[i].key);
}

int main(void)
{
	int r[N]={22,16,41,58,8,11,12,16,17,22,23,31,41,52,58,59,61};
	BTree T=NULL;
	Result s;
	int i;
	for(i=0; i<N; i++)
	{
		s = SearchBTree(T,r[i]);
		if(!s.tag)
			InsertBTree(&T, r[i], s.pt, s.i);
	}
	printf("\n输入待查关键字: ");
	scanf("%d", &i);
	s = SearchBTree(T, i);
	if(s.tag)
		Print(*(s.pt), s.i);
	else
		printf("没找到");
	printf("\n");
	return 0;
}
