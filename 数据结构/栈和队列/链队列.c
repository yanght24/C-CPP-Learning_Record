//只能尾进头出

#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int QElemType;	//定义数据元素类型
typedef int Status;		//定义函数类型, 其值为函数结构状态代码

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct 
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//初始化队列;
Status InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	
	return OK;
}

//若队列存在, 则销毁;
Status DestoryQueue(LinkQueue *Q)
{
	while(Q->front)		//队列空时, 结束循环
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;		//相当于front后移一位且与rear指向同一个元素
	}
	return OK;
}

//若队列为空, 返回true, 否则返回false;
Status EmptyQueue(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

//清空队列;
Status ClearQueue(LinkQueue *Q)
{
	QueuePtr p, q;	
	Q->rear = Q->front;		//front, rear都指向头结点
	p = Q->front->next;		//p指向第一个元素
	Q->front->next = NULL;	//删除第一个元素
	while(p)		//队列为空时, 结束循环
	{
		q = p;
		p = p->next;		//指针p后移一位
		free(q);
	}
	return OK;
}

//若队列存在且非空, 用e返回队头元素;
Status GetHead(LinkQueue Q, QElemType *e)
{
	QueuePtr p;
	if(Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;		//p指向第一个元素
	*e = p->data;
	
	return OK;
}

//若队列存在, 插入新元素e到队尾;
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s)		//存储空间分配失败
		return ERROR;
	s->data = e;		//将e赋给一个空结点
	s->next = NULL;
	Q->rear->next = s;	//把拥有e的新结点s赋给原队尾指针的后继
	Q->rear = s;		//将s设置为队尾结点
	
	return OK;
}

//删除队列的队头元素, 并用e返回其值;
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;		//将欲删除的队头结点暂存给p
	*e = p->data;			//将欲删除的队头结点的值赋给e
	Q->front->next = p->next;	//将原队头结点的后继即p->next赋给头结点的后继
	if(Q->rear == p)
		Q->rear = Q->front;
	free(p);
	
	return OK;
}

//返回队列的元素个数;
Status QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p;
	p = Q.front;
	while(p != Q.rear)
	{
		i++;
		p = p->next;	//p指针后移一位
	}
	return i;
}

//输出队列中的元素;
Status QueueVisit(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//从队头到队尾依次显示队列中的每个元素;
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p = Q.front->next;		//第一个元素
	while(p)
	{
		QueueVisit(p->data);
		p = p->next;
	}
	printf("\n");
	
	return OK;
}

int main(void)
{
	LinkQueue Q;
	QElemType e;
	Status i;
	
	i = InitQueue(&Q);
	printf("初始化Q后, Q.length = %d\n", QueueLength(Q));
	printf("初始化队列后，队列空否？%u (1: 空  0: 否)\n", EmptyQueue(Q));
	EnQueue(&Q,-5);
	EnQueue(&Q,5);
	EnQueue(&Q,10);
	printf("插入3个元素(-5,5,10)后,队列的长度为%d\n", QueueLength(Q));
	printf("是否空队列？%d (1: 空  0: 否) ", EmptyQueue(Q));
	printf("队列的元素依次为：");
	QueueTraverse(Q);
	
	DeQueue(&Q, &e);
	printf("删除队头元素: %d, 此时,队列的长度为: %d\n", e, QueueLength(Q));
	GetHead(Q, &e);
	printf("新的队头元素为: %d\n", e);
	ClearQueue(&Q);
	printf("清空队列后, Q.front=%d, q.rear=%d, q.front->next=%d\n", Q.front, Q.rear, Q.front->next);
	DestoryQueue(&Q);
	printf("销毁队列后, Q.front=%d, q.rear=%d\n", Q.front, Q.rear);
	
	return 0;
}
