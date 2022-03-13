//线性表的链式存储结构;
//用一组任意的存储单元存储线性表的数据元素;
//用n个结点链结成一个链表, 实现链式存储结构;
//第一个结点的存储位置叫头指针, 若存在头结点,则为指向头结点的指针;
//第一个结点前附设一个头结点, 其指针域存储指向第一个结点的指针;

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int ElemType;	//定义数据元素类型
typedef int Status;		//定义函数类型, 其值为函数结构状态代码

//定义一个单链表结构体
typedef struct Node		//定义结构体变量
{
	ElemType data;		//结点的数据域
	struct Node *next;	//结点的指针域
}Node;
typedef struct Node *LinkList;
//Node, *LinkList均为Node的别名, 但一个主要指代结点,一个主要指代链表
//结点由存放数据元素的数据域和存放后继结点的地址的指针域组成
//n个结点链成一个链表
//LinkList  L定义一个指针变量 (只改变结构体的内容, 不改变L的地址)
//此时*L为一个结构体
//LinkList *L定义一个指向结构体指针的指针 (会改变L的地址)
//此时**L为一个结构体

//初始化链式线性表;
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node));
	//产生头结点, 并使L指向此头结点
	if (!(*L))			//存储分配失败
		return ERROR;
	(*L)->next = NULL;	//指针域为空
	
	return OK;
}

//若线性表L为空,返回true,否则返回false;
Status EmptyList(LinkList L)
{
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

//清空线性表L;
Status ClearList(LinkList *L)
{
	LinkList p, s;
	p = (*L)->next;		//p指向L的第一个结点
	while( p )			//p没到表尾
	{
		s = p->next;	//将p的后继结点 ---> s
		free(p);		//释放p结点
		p = s;			//相当于将p后移1位继续清除
	}
	(*L)->next = NULL;	//头结点指针域为空
	
	return OK;
}

//用e返回L中第i个元素的值;
Status GetElem(LinkList L, int i, ElemType *e)
{
	int k;
	LinkList p;			//声明一个结点p
	p = L->next;		//p指向L的第一个结点
	k = 1;				//k为计数器
	while(p && k<i)		//p不为空或者计数器k不等于i时, 循环继续
	{
		p = p->next;	//p指向下一个结点
		++k;
	}
	if (!p || k>i)
		return ERROR;	//第i个元素不存在
	*e = p->data;
	
	return OK;
}

//在线性表L中查找与给定值e相等的元素并返回其序号;
Status LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next;
	while(p)
	{
		i++;
		if (p->data == e)
			return i;
		p = p->next;
	}
	return 0;
}

//在L中的第i个位置之前插入新的数据元素e, L的长度加1;
Status ListInsert(LinkList *L, int i, ElemType e)
{
	int k;
	LinkList p, s;
	p = *L;
	k = 1;
	while(p && k<i)		//p不为空或者计算器k不等于i时, 循环继续;
	{
		p = p->next;
		++k;
	}
	if (!p || k>i)
		return ERROR;
	s = (LinkList)malloc(sizeof(Node));	//生成一个新结点;
	s->data = e;		
	s->next = p->next;	//将p的后继结点 ---> s的后继结点
	p->next = s;		//将s ---> p的后继结点
	
	return OK;
}

//删除L的第i个数据元素, 并用e返回其值, L的长度减1;
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	int k;
	LinkList p, s;
	p = *L;
	k = 1;
	while(p->next && k<i)	//遍历寻找第i个元素
	{
		p = p->next;
		++k;
	}
	if (!(p->next) || k>i)
		return ERROR;
	s = p->next;		//将欲删除的结点p->next ---> s
	p->next = s->next;	//将s的后继结点 ---> p的后继结点
	*e = s->data;
	free(s);
	
	return OK;
}

//返回线性表L的元素个数;
Status ListLength(LinkList L)
{
	int i = 0;
	LinkList p;
	p = L->next;
	while(p)
	{
		++i;
		p = p->next;	
	}
	return i;
}

//输出线性表L中的元素
Status ListVisit(ElemType c)
{
	printf("%d ", c);
	return OK;
}

//依次对L的每个数据元素输出;
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;
	while(p)
	{
		ListVisit(p->data);
		p = p->next;
	}
	printf("\n");
	
	return OK;
}

//随机产生n个元素的值，建立带表头结点的单链线性表L (头插法)
Status CreateListHead(LinkList *L, int n)
{
	LinkList p;
	int i;
	srand(time(0));		//初始化随机数种子
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;	//建立一个带头结点的单链表
	for(i=0; i<n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));	//生成一个新结点
		p->data = rand()%100+1;		//随机生成100以内的数字
		p->next = (*L)->next;		//将头结点后继结点 ---> p的后继结点
		(*L)->next = p;				//将p ---> 头结点后继结点			
	}
	return OK;
}

//随机产生n个元素的值，建立带表头结点的单链线性表L (尾插法)
Status CreateListTail(LinkList *L, int n)
{
	LinkList p, s;
	int i;
	srand(time(0));		//初始化随机数种子
	*L = (LinkList)malloc(sizeof(Node));
	s = *L;				//生成一个指向尾部的结点s
	for(i=0; i<n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));	//生成一个新节点
		p->data = rand()%100+1;		//随机生成100以内的数字
		s->next = p;				//将表尾终端结点指针指向新结点;
		s = p;						//将p ---> 表尾终端结点, 始终将s指向尾部
	}
	s->next = NULL;					//循环结束后, 将尾部结点指针域置空
	
	return OK;
}

int main(void)
{
	LinkList L;
	ElemType e;
	Status i;
	int j, k;
	
	i = InitList(&L);
	printf("初始化线性表L后, L.length = %d\n", ListLength(L));
	for(j=1; j<=5; j++)
		i = ListInsert(&L, 1, j);
	printf("在L的表头依次插入1~5后, L.data = ");
	ListTraverse(L);
	printf("此时, L.length = %d\n", ListLength(L));
	printf("\n");
	
	i = EmptyList(L);
	printf("L是否为空, i = %d (1: 是  0: 否)\n", i);
	i = ClearList(&L);
	printf("清空L后, L,length = %d\n", ListLength(L));
	i = EmptyList(L);
	printf("L是否为空, i = %d (1: 是  0: 否)\n", i);
	printf("\n");
	
	for(j=1; j<=10; j++)
		ListInsert(&L, j, j);
	printf("在L的表尾依次插入1~10后, L.data = ");
	ListTraverse(L);
	printf("此时, L.length = %d\n", ListLength(L));
	printf("\n");
	
	ListInsert(&L, 1, 0);
	printf("在L的表头插入0后, L.data = ");
	ListTraverse(L);
	printf("此时, L.length = %d\n", ListLength(L));
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
	
	j=5;
	ListDelete(&L,j,&e); /* 删除第5个数据 */
	printf("删除第%d个的元素值为：%d\n",j,e);	
	printf("依次输出L的元素：");
	ListTraverse(L); 
	
	i=ClearList(&L);
	printf("\n清空L后：ListLength(L)=%d\n",ListLength(L));
	CreateListHead(&L,20);
	printf("整体创建L的元素(头插法)：");
	ListTraverse(L);
	
	i=ClearList(&L);
	printf("\n删除L后：ListLength(L)=%d\n",ListLength(L));
	CreateListTail(&L,20);
	printf("整体创建L的元素(尾插法)：");
	ListTraverse(L); 
	
	return 0;
}







