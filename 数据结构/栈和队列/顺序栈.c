//栈的顺序存储即线性表顺序存储的简化

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
	int top;			//栈顶指针即当前栈顶元素的下标值
}SqStack;

//初始化顺序栈;
Status InitStack(SqStack *S)
{
	S->top = -1;			//空栈, 第一个元素入栈时自加指向0元素
	return OK;
}

//若栈存在, 则销毁
Status DestoryStack(SqStack *S)
{
	if (S->top != -1)
		S->top = -1;
	
	return OK;
}

//若栈为空, 返回true, 否则返回false;
Status EmptyStack(SqStack S)
{
	if (S.top == -1)
		return TRUE;
	else
		return FALSE;
}

//清空栈;
Status ClearStack(SqStack *S)
{
	S->top = -1;
	return OK;
}

//若栈存在且非空, 用e返回栈顶元素;
Status GetTop(SqStack S, SElemType *e)
{
	if (S.top == -1)
		return ERROR;
	*e = S.data[S.top];
	
	return OK;
}

//若栈存在, 插入新元素e到栈顶;
Status Push(SqStack *S, SElemType e)
{
	if (S->top == MAXSIZE-1)	//判断是否栈满
		return ERROR;
	S->top++;					//栈顶指针加1
	S->data[S->top] = e;
	
	return OK;
}

//删除栈的栈顶元素, 并用e返回其值;
Status Pop(SqStack *S, SElemType *e)
{
	if (S->top == -1)
		return ERROR;
	*e = S->data[S->top];
	S->top--;
	
	return OK;
}

//返回栈的元素个数;
Status StackLength(SqStack S)
{
	return S.top+1;
}

//输出栈中的元素;
Status StackVisit(SElemType c)
{
	printf("%d ", c);
	return OK;
}

//从栈底到栈顶依次显示栈中的每个元素;
Status StackTraverse(SqStack S)
{
	int i;
	for(i=0; i<=S.top; i++)
	{
		StackVisit(S.data[i]);
	}
	printf("\n");
	
	return OK;
}

int main(void)
{
	SqStack S;
	SElemType e;
	Status i;
	int j;
	
	i = InitStack(&S);
	printf("初始化S后, S.length = %d\n", StackLength(S));
	for(j=1; j<=10; j++)
		i = Push(&S, j);
	printf("将1~10依次入栈后, S.data = ");
	StackTraverse(S);
	printf("此时, S.length = %d\n", StackLength(S));
	printf("\n");
	
	i = EmptyStack(S);
	printf("S是否为空, i = %d (1: 是  0: 否)\n", i);
	i = ClearStack(&S);
	printf("清空S后, S.length = %d\n", StackLength(S));
	i = EmptyStack(S);
	printf("S是否为空, i = %d (1: 是  0: 否)\n", i);
	printf("\n");
	
	for(j=1; j<=5; j++)
		i = Push(&S, j);
	printf("将1~5依次入栈后, S.data = ");
	StackTraverse(S);
	Push(&S, 6);
	printf("再将6入栈后, S,data = ");
	StackTraverse(S);
	Pop(&S, &e);
	printf("弹出的栈顶元素 e=%d\n", e);
	GetTop(S, &e);
	printf("栈顶元素 e=%d 栈的长度为%d\n", e, StackLength(S));
	
	return 0;
}
