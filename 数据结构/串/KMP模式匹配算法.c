//为了省略没必要的回溯
//查找字符串前, 先对要查找的字符分析

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;		//函数结果状态代码
typedef int ElemType;	//数据类型定义

typedef char String[MAXSIZE+1];	//0号单元存放串的长度

//生成1个其值等于字符串常量chars的串T;
Status StrAssign(String T, char *chars)
{
	int i;
	if (strlen(chars)>MAXSIZE)
		return ERROR;
	else
	{	
		T[0] = strlen(chars);
		for(i=1; i<=T[0]; i++)
			T[i] = *(chars+i-1);
		return OK;
	}
}

//串S存在, 则清空;
Status ClearString(String S)
{
	S[0] = 0;
	return OK;
}

//输出字符串T;
Status StrPrint(String T)
{ 
	int i;
	for(i=1;i<=T[0];i++)
		printf("%c",T[i]);
	printf("\n");
	
	return OK;
}

//输出next数组值;
Status NextPrint(int next[], int length)
{
	int i;
	for(i=1; i<=length; i++)
		printf("%d", next[i]);
	printf("\n");
	
	return OK;
}

//返回串S的元素个数;
Status StrLength(String S)
{
	return S[0];
}

//朴素的模式匹配算法;
Status Index(String S, String T, int pos)
{
	int i = pos;		//主串S中当前位置的下标
	int j = 1;			//子串T中当前位置的下标
	while(i<=S[0] && j<=T[0])	//i不大于S的长度且j不大于T的长度
	{
		if (S[i] == T[j])		//相等则继续匹配
		{
			++i;
			++j;
		}
		else		//指针后退重新开始匹配
		{
			i = i-j+2;	//i退至上次匹配首位的下一位
			j = 1;		//j退至子串T的首位
		}
	}
	if (j > T[0])
		return i-T[0];
	else
		return FALSE;
}

//通过计算返回字符T的next数组
Status GetNext(String T, int *next)
{
	int i, k;
	i = 1;		//子串T从第一个元素起开始分析
	k = 0;		//计算以得到next数组
	next[1] = 0;
	while(i < T[0])
	{
		if (k==0 || T[i]==T[k])	
		{
			++i;
			++k;
			next[i] = k;
		}
		else
			k = next[k];	//若字符不相同, 则k值回溯
	}
	return OK;
}

//返回子串T在主串S中第pos个字符之后的位置;
int Index_KMP(String S, String T, int pos)
{
	int i = pos;		//主串S中当前位置的下标
	int j = 1;			//子串T中当前位置的下标
	int next[255];
	GetNext(T, next);	//对T分析得到next数组
	while(i<=S[0] && j<=T[0])
	{
		if (j==0 || S[i]==T[j])		//相等则继续匹配
		{
			++i;
			++j;
		}
		else
			j = next[j];	//j退至合适的位置, i不变
	}
	if (j > T[0])
		return i-T[0];
	else
		return FALSE;
}

//求模式串T的next函数修正值并存入数组nextval;
Status GetNextval(String T, int *nextval)
{
	int i, k;
	i = 1;
	k = 0;
	nextval[1] = 0;
	while(i < T[0])
	{
		if (k==0 || T[i]==T[k])
		{
			++i;
			++k;
			if (T[i]!=T[k])			//若当前字符与前缀字符不同
				nextval[i] = k;		//则当前的k为nextval在i位置的值
			else							//若当前字符与前缀字符相同
				nextval[i] = nextval[k];	//则将前缀字符的nextval赋给nextval在i位置的值
		}
		else
			k = nextval[k];			//若字符不同, 则k值回溯
	}
	return OK;
}

int Index_KMP1(String S, String T, int pos)
{
	int i = pos;		//主串S中当前位置的下标
	int j = 1;			//子串T中当前位置的下标
	int next[255];
	GetNextval(T, next);	//对T分析得到next数组
	while(i<=S[0] && j<=T[0])
	{
		if (j==0 || S[i]==T[j])		//相等则继续匹配
		{
			++i;
			++j;
		}
		else
			j = next[j];	//j退至合适的位置, i不变
	}
	if (j > T[0])
		return i-T[0];
	else
		return FALSE;
}

int main(void)
{
	int i, *p;
	String S, T;
	
	StrAssign(S, "abcdex");
	printf("子串为: ");
	StrPrint(S);
	i = StrLength(S);
	p = (int*)malloc((i+1)*sizeof(int));
	GetNext(S, p);
	printf("Next为: ");
	NextPrint(p, StrLength(S));
	printf("\n");
	
	StrAssign(S, "abcabx");
	printf("子串为: ");
	StrPrint(S);
	i = StrLength(S);
	p = (int*)malloc((i+1)*sizeof(int));
	GetNext(S, p);
	printf("Next为: ");
	NextPrint(p, StrLength(S));
	printf("\n");
	
	StrAssign(S, "ababaaaba");
	printf("子串为: ");
	StrPrint(S);
	i = StrLength(S);
	p = (int*)malloc((i+1)*sizeof(int));
	GetNext(S, p);
	printf("Next为: ");
	NextPrint(p, StrLength(S));
	printf("\n");
	
	StrAssign(S, "aaaaaaaab");
	printf("子串为: ");
	StrPrint(S);
	i = StrLength(S);
	p = (int*)malloc((i+1)*sizeof(int));
	GetNext(S, p);
	printf("Next为: ");
	NextPrint(p, StrLength(S));
	printf("\n");
	
	StrAssign(S, "ababaaaba");
	printf("   子串为: ");
	StrPrint(S);
	i = StrLength(S);
	p = (int*)malloc((i+1)*sizeof(int));
	GetNext(S, p);
	printf("   Next为: ");
	NextPrint(p, StrLength(S));
	GetNextval(S, p);
	printf("NextVal为: ");
	NextPrint(p, StrLength(S));
	printf("\n");
	
	StrAssign(S, "aaaaaaaab");
	printf("   子串为: ");
	StrPrint(S);
	i = StrLength(S);
	p = (int*)malloc((i+1)*sizeof(int));
	GetNext(S, p);
	printf("   Next为: ");
	NextPrint(p, StrLength(S));
	GetNextval(S, p);
	printf("NextVal为: ");
	NextPrint(p, StrLength(S));
	printf("\n");
	
	StrAssign(S, "00000000000000000000000000000000000000000000000001");
	printf("主串S为: ");
	StrPrint(S);
	StrAssign(T, "0000000001");
	printf("子串T为: ");
	StrPrint(T);
	printf("\n");
	printf("主串S和子串T在第%d个字符处首次匹配（朴素模式匹配算法）\n", Index(S, T, 1));
	printf("主串S和子串T在第%d个字符处首次匹配（KMP算法） \n", Index_KMP(S, T, 1));
	printf("主串S和子串T在第%d个字符处首次匹配（KMP改良算法）\n", Index_KMP1(S, T, 1));
	
	return 0;
}























