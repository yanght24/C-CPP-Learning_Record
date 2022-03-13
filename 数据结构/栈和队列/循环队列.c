//头尾相接的顺序存储结构
//队列满: (rear+1)%QueueSize == front
//队列长: (rear-front+QueueSize)%QueueSize

#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int QElemType;	//定义数据元素类型
typedef int Status;		//定义函数类型, 其值为函数结构状态代码

typedef struct
{
	QElemType data[MAXSIZE];
	int front;		//头指针
	int rear;		//尾指针, 若队列不空, 指向队尾元素的下一个位置
}SqQueue;

//初始化队列;
Status InitQueue(SqQueue *Q)
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//若队列存在, 则销毁;
Status DestoryQueue(SqQueue *Q)
{
	if (Q->front != Q->rear)
		free(Q->data);
	Q->front = 0;
	Q->rear = 0;
	
	return OK;
}

//若队列为空, 返回true, 否则返回false;
Status EmptyQueue(SqQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

//清空队列;
Status ClearQueue(SqQueue *Q)
{
	Q->front=Q->rear=0;
	return OK;
}

//若队列存在且非空, 用e返回队头元素;
Status GetHead(SqQueue Q, QElemType *e)
{
	if (Q.front == Q.rear)
		return ERROR;
	*e = Q.data[Q.front];
	
	return OK;
}

//若队列存在, 插入新元素e到队尾;
Status EnQueue(SqQueue *Q, QElemType e)
{
	if ((Q->rear+1)%MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear+1) % MAXSIZE;	//若到最后则转到头部
	
	return OK;
}

//删除队列的队头元素, 并用e返回其值;
Status DeQueue(SqQueue *Q, QElemType *e)
{
	if (Q->front == Q->rear)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front+1) % MAXSIZE;	//若到最后则转到头部
	
	return OK;
}

//返回队列的元素个数;
Status QueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

//输出队列中的元素;
Status QueueVisit(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//从队头到队尾依次显示队列中的每个元素;
Status QueueTraverse(SqQueue Q)
{
	int i;
	i = Q.front;
	while(i != Q.rear)
	{
		QueueVisit(Q.data[i]);
		i = (i+1)%MAXSIZE;
	}
	printf("\n");
	
	return OK;
}

int main(void)
{
	SqQueue Q;
	QElemType e;
	Status i = 0;
	int j, k;
	
	InitQueue(&Q);
	printf("初始化Q后, Q.length = %d\n", QueueLength(Q));
	printf("初始化队列后，队列空否？%u (1: 空  0: 否)\n", EmptyQueue(Q));
	
	printf("进行%d次入队操作后, Q.data: ", MAXSIZE-1);
	do{
		e = i + 100;
		i++;
		EnQueue(&Q, e);
	}while(i<MAXSIZE-1);
	QueueTraverse(Q);
	printf("此时, 队列长度为: %d\n",QueueLength(Q));
	printf("现在队列空否？%u(1:空 0:否)\n", EmptyQueue(Q));
	printf("\n");
	
	printf("连续%d次由队头删除元素,队尾插入元素:\n",MAXSIZE);
	for(k=1; k<=MAXSIZE; k++)
	{
		DeQueue(&Q, &e);
		printf("删除的元素是: %d, 插入的元素是: %d\n", e, k+1000);
		e = k+1000;
		EnQueue(&Q, e);
	}
	printf("此时, Q.data: \n");
	QueueTraverse(Q);
	printf("此时, 队列长度为: %d\n",QueueLength(Q));
	printf("\n");
	
	printf("共向队尾插入了%d个元素\n",i+MAXSIZE);
	if(k-2>0)			//k = MAXSIZE+1即21
		printf("现在由队头删除%d个元素:\n", k-2);
	while(QueueLength(Q)>2)
	{
		DeQueue(&Q, &e);
		printf("删除的元素值为%d\n", e);
	}
	
	j = GetHead(Q, &e);
	if(j)			//当队列为空时, 结束循环
		printf("现在的队头元素是: %d\n", e);
	printf("此时, Q.data: \n");
	QueueTraverse(Q);
	ClearQueue(&Q);
	printf("清空队列后, 队列空否？%u(1:空 0:否)\n", EmptyQueue(Q));
	
	return 0;
}
