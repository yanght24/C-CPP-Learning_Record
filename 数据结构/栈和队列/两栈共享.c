//用一个数组存储两个栈, 分别自始端和末端向数组中间延伸

#include<stdio.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20		//存储空间初始分配量

typedef int SElemType;	//定义数据元素类型
typedef int Status;		//定义函数类型, 其值为函数结构状态代码

typedef struct
{
	SElemType data[MAXSIZE];
	int top1;		//栈1的栈顶指针	
	int top2;		//栈2的栈顶指针
}SqDoubleStack;			//栈顶指针即当前栈顶元素的下标值

//初始化栈;
Status InitStack(SqDoubleStack *S)
{
	S->top1 = -1;			//栈1空, 第一个元素入栈时自加
	S->top2 = MAXSIZE;		//栈2空, 第一个元素入栈时自减
	return OK;
}

//若栈存在, 则销毁
Status DestoryStack(SqDoubleStack *S)
{
	if (S->top1!=-1 || S->top2!=MAXSIZE)
	{
		S->top1 = -1;
		S->top2 = MAXSIZE;
	}
	return OK;
}

//若栈为空, 返回true, 否则返回false;
Status EmptyStack(SqDoubleStack S)
{
	if (S.top1==-1 && S.top2==MAXSIZE)
		return TRUE;
	else
		return FALSE;
}

//清空栈;
Status ClearStack(SqDoubleStack *S)
{
	S->top1 = -1;
	S->top2 = MAXSIZE;
	return OK;
}

//若栈存在且非空, 用e返回栈顶元素;
Status GetTop(SqDoubleStack S, SElemType *e, int StackNumber)
{
	if (StackNumber == 1)
	{
		if (S.top1 == -1)
			return ERROR;
		*e = S.data[S.top1];
	}
	else if (StackNumber == 2)
	{
		if (S.top2 == MAXSIZE)
			return ERROR;
		*e = S.data[S.top2];
	}
	return OK;
}

//若栈存在, 插入新元素e到栈顶;
Status Push(SqDoubleStack *S, SElemType e, int StackNumber)
{
	if (S->top1+1 == S->top2)		//判断是否栈满
		return ERROR;
	if (StackNumber == 1)
		S->data[++S->top1] = e;		//栈1, 则先top1+1后再给数组元素赋值
	else if (StackNumber == 2)
		S->data[--S->top2] = e;		//栈2, 则先top2-1后再给数组元素赋值
	
	return OK;
}

//若栈存在, 删除栈顶元素, 并用e返回其值;
Status Pop(SqDoubleStack *S, SElemType *e, int StackNumber)
{
	if (StackNumber == 1)
	{
		if (S->top1 == -1)
			return ERROR;
		*e = S->data[S->top1--];	//栈1, 先将栈顶元素赋给e再出栈
	}
	if (StackNumber == 2)
	{
		if (S->top1 == MAXSIZE)
			return ERROR;
		*e = S->data[S->top2++];	//栈2, 先将栈顶元素赋给e再出栈
	}
	
	return OK;
}

//输出栈中的元素;
Status StackVisit(SElemType c)
{
	printf("%d ", c);
	return OK;
}

//返回栈的元素个数;
Status StackLength(SqDoubleStack S)
{
	return (S.top1+1)+(MAXSIZE-S.top2);
}

//从栈底到栈顶依次显示栈中的每个元素;
Status StackTraverse(SqDoubleStack S)
{
	int i;
	i = 0;
	while(i <= S.top1)
	{
		StackVisit(S.data[i++]);
	}
	i = S.top2;
	while(i < MAXSIZE)
	{
		StackVisit(S.data[i++]);
	}
	printf("\n");
	
	return OK;
}

int main(void)
{
	SqDoubleStack S;
	SElemType e;
	int j;
	
	InitStack(&S);
	printf("初始化S后, S.length = %d\n", StackLength(S));
	for(j=1; j<=5; j++)
		Push(&S, j, 1);
	for(j=MAXSIZE; j>=MAXSIZE-2; j--)
		Push(&S, j, 2);
	printf("分别入栈后, 栈中元素依次为S.data = ");
	StackTraverse(S);
	printf("此时, S.length = %d\n", StackLength(S));
	printf("\n");
	
	Pop(&S, &e, 1);
	printf("弹出栈1的栈顶元素: %d\n", e);
	Pop(&S, &e, 2);
	printf("弹出栈2的栈顶元素: %d\n", e);
	printf("此时, S.length = %d\n, 栈中元素依次为S.data = ", StackLength(S));
	StackTraverse(S);
	printf("\n");
	
	printf("栈是否为空: %d (1: 是  0: 否)\n", EmptyStack(S));
	ClearStack(&S);
	printf("清空栈后, 栈是否为空: %d (1: 是  0: 否)\n", EmptyStack(S));
	
	return 0;
}
