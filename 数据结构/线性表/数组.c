//线性表的顺序存储结构;
//用一段地址连续的存储单元依次存储线性表的数据元素;
//用一维数组实现顺序存储结构;

#include<stdio.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20		//存储空间初始分配量

typedef int ElemType;	//定义数据元素类型
typedef int Status;		//定义函数类型, 其值为函数结构状态代码

typedef struct
{
	ElemType data[MAXSIZE];	//数组，存储数据元素
	int length;				//线性表当前的长度
}SqList;

//初始化顺序线性表;
Status InitList(SqList *L)
{
	L->length = 0;
	return OK;
}

//若线性表L为空,返回true,否则返回false;
Status EmptyList(SqList L)
{
	if (L.length == 0)
		return TRUE;
	else
		return FALSE;
}

//清空线性表L;
Status ClearList(SqList *L)
{
	L->length = 0;
	return OK;
}

//用e返回L中第i个元素的值;
Status GetElem(SqList L, int i, ElemType *e)
{
	if(L.length==0 || i<1 || i>L.length)
		return ERROR;
	*e = L.data[i-1];	//第i个位置元素对应数组第i-1下标的值
	
	return OK;
}

//在线性表L中查找与给定值e相等的元素并返回其序号;
Status LocateElem(SqList L, ElemType e)
{
	int i;
	if (L.length == 0)
		return ERROR;
	for(i=1; i<=L.length; i++)
	{
		if (L.data[i-1] == e)
			break;
	}
	if (i>L.length)
		return FALSE;
	
	return i;
}

//在L中的第i个位置之前插入新的数据元素e, L的长度加1;
Status ListInsert(SqList *L, int i, ElemType e)
{
	int k;
	if (L->length == MAXSIZE)
		return ERROR;
	if (i<1 || i>L->length+1)	//i比第1位置小或者比最后1位后1位置大
		return ERROR;
	if (i<=L->length)			//插入位置不在表尾
	{
		for(k=L->length-1; k>=i-1; k--)
			L->data[k+1] = L->data[k];
		//下标为length-1到i-1即最后1个到第i个元素全部后移1位
	}
	L->data[i-1] = e;	//在下标i-1即第i个位置上插入新的数据元素e
	L->length++;		//表长加1
	
	return OK;
}

//删除L的第i个数据元素, 并用e返回其值, L的长度减1;
Status ListDelete(SqList *L, int i, ElemType *e)
{
	int k;
	if (L->length == 0)
		return ERROR;
	if (i<1 || i>L->length)		//删除位置不合理
		return ERROR;
	*e = L->data[i-1];			//将下标为i-1即第i个元素的值赋给e
	if (i<L->length)
	{
		for(k=i; k<L->length; k++)
			L->data[k-1] = L->data[k];
			//下标为i到length-1即第i+1个到最后一个元素全部前移1位
	}
	L->length--;	//表长减1
	
	return OK;
}

//返回线性表L的元素个数;
Status ListLength(SqList L)
{
	return L.length;
}

//输出线性表L中的元素
Status ListVisit(ElemType c)
{
	printf("%d ", c);
	return OK;
}

//依次对L的每个数据元素输出;
Status ListTraverse(SqList L)
{
	int i;
	for(i=1; i<=L.length; i++)
		ListVisit(L.data[i-1]);
	printf("\n");
	
	return OK;
}

//将所有在线性表Lb但不在La中的数据全部插入到La中;
Status ListUnion(SqList *La, SqList Lb)
{
	int La_len, Lb_len, i;
	ElemType e;		//声明La与Lb相同的数据元素e
	La_len = ListLength(*La);		//求得线性表的长度
	Lb_len = ListLength(Lb);
	for(i = 1; i<=Lb_len; i++)
	{
		GetElem(Lb, i, &e);			//取出Lb中第i个数据元素赋给e
		if (!LocateElem(*La, e))	//La中不存在和e相同的数据元素
			ListInsert(La, ++La_len, e);
	}
	return OK;
}

int main(void)
{
	SqList L;
	SqList L2;
	ElemType e;
	Status i;
	int j, k;
	
	i = InitList(&L);
	printf("初始化线性表L后, L.length = %d\n", L.length);
	for(j=1; j<=5; j++)
		i = ListInsert(&L, 1, j);
	printf("在L的表头依次插入1~5后, L.data = ");
	ListTraverse(L);
	printf("此时, L.length = %d\n", L.length);
	printf("\n");
	
	i = EmptyList(L);
	printf("L是否为空, i = %d (1: 是  0: 否)\n", i);
	i = ClearList(&L);
	printf("清空L后, L.length = %d\n", L.length);
	i = EmptyList(L);
	printf("L是否为空, i = %d (1: 是  0: 否)\n", i);
	printf("\n");
	
	for(j=1; j<=10; j++)
		ListInsert(&L, j, j);
	printf("在L的表尾依次插入1~10后, L.data = ");
	ListTraverse(L);
	printf("此时, L.length = %d\n", L.length);
	printf("\n");
	
	ListInsert(&L, 1, 0);
	printf("在L的表头插入0后, L.data = ");
	ListTraverse(L);
	printf("此时, L.length = %d\n", L.length);
	printf("\n");
	
	GetElem(L, 5, &e);
	printf("L中第5个元素的值是: %d\n", e);
	for(j=8; j<=12; j++)
	{
		k = LocateElem(L, j);
		if (k)
			printf("L中第%d个元素的值是%d\n", k, j);
		else
			printf("L中没有值为%d的元素\n", j);
	}
	printf("\n");
	
	k = ListLength(L);
	for(j=k+1; j>=k; j--)
	{
		i = ListDelete(&L, j, &e);
		if (i==ERROR)
			printf("L中删除第%d个元素失败\n", j);
		else
			printf("L中删除第%d个元素的值为: %d\n", j, e);
	}
	printf("依次输出L的元素: ");
	ListTraverse(L);
	printf("\n");
	
	//构造一个有10个数的L2
	i = InitList(&L2);
	for(j=6; j<=15; j++)
		i = ListInsert(&L2, 1, j);
	printf("\n");
	
	printf("构造后, 依次输出L2的元素: ");
	ListTraverse(L2);
	ListUnion(&L, L2);
	printf("依次输出合并L2后L的元素: ");
	ListTraverse(L);
	
	return 0;
}
