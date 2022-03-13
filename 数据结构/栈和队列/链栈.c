//将栈顶放在单链表的头部, 链栈不需要头结点, 且长度无限制

#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int SElemType;	//定义数据元素类型
typedef int Status;		//定义函数类型, 其值为函数结构状态代码

typedef struct StackNode
{
	SElemType data;
	struct StackNode *next;
}StackNode, *LinkStackPtr;		//LinkStackPtr作为StackNode的指针

typedef struct
{
	LinkStackPtr top;			//作为栈顶指针
	int count;
}LinkStack;						//将StackNode的指针嵌入到LinkStack的结构中

//初始化链栈;
Status InitStack(LinkStack *S)
{
	S->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if (!S->top)
		return ERROR;
	S->top = NULL;
	S->count = 0;
	return OK;
}

//若栈为空栈，返回true, 否则返回false;
Status StackEmpty(LinkStack S)
{ 
	if (S.count==0)
		return TRUE;
	else
		return FALSE;
}

//清空栈;
Status ClearStack(LinkStack *S)
{
	LinkStackPtr p, q;
	p = S->top;			//定义指针p指向栈顶
	while(p)
	{
		q = p;
		p = p->next;	//后移一位
		free(q);
	}
	S->count = 0;
	
	return OK;
}

//若栈存在且非空, 用e返回栈顶元素;
Status GetTop(LinkStack S, SElemType *e)
{
	if (S.top == NULL)
		return ERROR;
	else
		*e = S.top->data;
	
	return OK;
}

//若栈存在, 插入新元素e到栈顶;
Status Push(LinkStack *S, SElemType e)
{
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->data = e;		//将元素值为e的新结点定义为s
	s->next = S->top;	//将当前的栈顶元素赋给新结点的直接后继
	S->top = s;
	S->count++;
	
	return OK;
}

//删除栈顶元素, 并用e返回其值;
Status Pop(LinkStack *S, SElemType *e)
{
	LinkStackPtr p;
	if (StackEmpty(*S))
		return ERROR;
	*e = S->top->data;
	p = S->top;				//将栈顶结点赋值给p
	S->top = S->top->next;	//栈顶指针下移一位, 指向后一结点
	free(p);
	S->count--;
	
	return OK;
}

//返回栈的元素个数;
Status StackLength(LinkStack S)
{
	return S.count;
}

//输出栈中的元素;
Status StackVisit(SElemType c)
{
	printf("%d ", c);
	return OK;
}

//从栈底到栈顶依次显示栈中的每个元素;
Status StackTraverse(LinkStack S)
{
	LinkStackPtr p;
	p = S.top;
	while(p)
	{
		StackVisit(p->data);
		p = p->next;
	}
	printf("\n");
	
	return OK;
}

int main(void)
{
	LinkStack S;
	SElemType e;
	int j;
	
	InitStack(&S);
	printf("初始化S后, S.length = %d\n", StackLength(S));
	for(j=1; j<=10; j++)
		Push(&S, j);
	printf("依次入栈后, 栈中元素依次为S.data = ");
	StackTraverse(S);
	printf("此时, S.length = %d\n", StackLength(S));
	printf("\n");
	
	Pop(&S, &e);
	printf("弹出的栈顶元素 e=%d\n", e);
	GetTop(S, &e);
	printf("栈顶元素 e=%d 栈的长度为%d\n", e, StackLength(S));
	printf("此时, S.data = ");
	StackTraverse(S);
	
	printf("栈是否为空: %d (1: 是  0: 否)\n",StackEmpty(S));
	ClearStack(&S);
	printf("清空栈后，栈是否为空: %d (1: 是  0: 否)\n",StackEmpty(S));
	
	return 0;
}
