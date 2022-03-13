//用一组地址连续的存储单元来存储串中的字符序列

#include<stdio.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 40 /* 存储空间初始分配量 */

typedef int Status;		//函数结果状态代码
typedef int ElemType;	//数据类型定义

typedef char String[MAXSIZE+1];	//0号单元存放串的长度

//生成1个其值等于字符串常量chars的串T;
Status StrAssign(String T, char *chars)
{
	int i;
	if (strlen(chars) > MAXSIZE)	//判断是否会上溢
		return ERROR;
	else
	{
		T[0] = strlen(chars);		//存放串的长度
		for(i=1; i<=T[0]; i++)		
			T[i] = *(chars+i-1);	//指向chars的每一个元素
		return OK;
	}
}

//串S存在, 由串S复制得串T;
Status StrCopy(String T, String S)
{
	int i;
	for(i=0; i<=S[0]; i++)
		T[i] = S[i];
	return OK;
}

//串S存在, 则清空;
Status ClearString(String S)
{
	S[0] = 0;
	return OK;
}

//若串S存在, 返回true, 否则返回false;
Status EmptyString(String S)
{
	if (S[0] == 0)
		return TRUE;
	else
		return FALSE;
}

//返回串S的元素个数;
Status StrLength(String S)
{
	return S[0];
}

//S>T, 返回值>0; S=T, 返回0; S<T, 返回值<0;
Status StrCompare(String S, String T)
{
	int i;
	for(i=1; i<=S[0]&&i<=T[0]; ++i)
		if (S[i] != T[i])		//比较每个元素大小
			return S[i]-T[i];
	return S[0]-T[0];			//长度不同时, 返回长度差
}

//用T返回由S1和S2连接而成的新串;
Status Concat(String T, String S1, String S2)
{
	int i;
	if (S1[0]+S2[0] <= MAXSIZE)	//未被截断
	{
		for(i=1; i<=S1[0]; i++)
			T[i] = S1[i];		//将S1全部传入T
		for(i=1; i<=S2[0]; i++)
			T[i+S1[0]] = S2[i];	//将S2全部传入T
		T[0] = S1[0]+S2[0];
		return TRUE;
	}
	else						//S2被截断
	{
		for(i=1; i<=S1[0]; i++)
			T[i] = S1[i];
		for(i=1; i<=MAXSIZE-S1[0]; i++)
			T[S1[0]+i] = S2[i];
		T[0] = MAXSIZE;
		return FALSE;
	}
}

//用Sub返回串S的第pos个字符起长度为len的字串;
Status SubString(String Sub, String S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1)
		return ERROR;
	for(i=1; i<=len; i++)
		Sub[i] = S[pos+i-1];
	Sub[0] = len;
	
	return OK;
}

//返回子串T在主串S中第pos个字符之后的位置;
Status Index(String S, String T, int pos)
{
	int i = pos;	//主串S中当前位置的下标
	int j = 1;		//子串T中当前位置的下标
	while(i<=S[0] && j<=T[0])	//i不大于S的长度且j不大于T的长度
	{
		if (S[i] == T[j])		//相等则继续匹配
		{
			++i;
			++j;
		}
		else		//指针后退重新开始匹配
		{
			i = i-j+2;			//i退至上次匹配首位的下一位
			j = 1;				//j退至子串T的首位
		}
	}
	if (j > T[0])
		return i-T[0];
	else
		return FALSE;
}

//主串S中第pos个字符后存在与T相等的子串, 返回第一个这个的子串出现的位置;
Status Index2(String S, String T, int pos)
{
	int i, n, m;
	String Sub;
	if (pos > 0)
	{
		n = StrLength(S);	
		m = StrLength(T);
		i = pos;
		while(i <= n-m+1)
		{
			SubString(Sub, S, i, m);	//取主串中第i个位置长度与T相等的子串给Sub
			if (StrCompare(Sub, T) != 0)	//判断两串是否相等
				i++;					//位置后移
			else
				return i;
		}
	}
	return FALSE;
}

//在串S的第pos个字符之前插入串T;
Status StrInsert(String S, int pos, String T)
{
	int i;
	if (pos<1 || pos>S[0]+1)	//插入位置错误
		return ERROR;
	if (S[0]+T[0] <= MAXSIZE)
	{
		for(i=S[0]; i>=pos; i--)
			S[i+T[0]] = S[i];	//相当于将pos后的元素后移T[0]以插入串T
		for(i=pos; i<pos+T[0]; i++)
			S[i] = T[i-pos+1];	//相当于将T中元素从pos开始依次插入
		S[0] = S[0] + T[0];
		return OK;
	}
	else			//部分插入
	{
		for(i=MAXSIZE; i<=pos; i--)
			S[i] = S[i-T[0]];	//相当于将pos后的元素挪到串尾
		for(i=pos; i<pos+T[0]; i++)
			S[i] = T[i-pos+1];
		S[0] = MAXSIZE;
		return FALSE;
	}
}

//从串S中删除第pos个字符起长度为len的子串;
Status StrDelete(String S,int pos,int len)
{
	int i;
	if (pos<1 || pos>S[0]-len+1 || len<0)
		return ERROR;
	for(i=pos+len; i<=S[0]; i++)
		S[i-len] = S[i];
	S[0] -= len;
	return OK;
}

//用V替换主串S中出现所有与T相等的不重叠的子串;
Status Replace(String S, String T, String V)
{
	int i = 1;
	if (EmptyString(T))
		return ERROR;
	do{
		i = Index(S, T, i);		//i为上一个i之后找到子串T的位置
		if (i)
		{
			StrDelete(S, i, StrLength(T));		//删除该子串T
			StrInsert(S, i, V);					//原位置上插入V
			i += StrLength(V);	//在插入的串V后继续查找串T
		}
	}while(i);
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

int main(void)
{
	int n, m;
	Status i;
	char s;
	String t, s1, s2;
	
	printf("Let string s1 = 'abcd'\n");
	i = StrAssign(s1, "abcd");
	if (!i)
		printf("串长度超过MAXSIZE(=%d)\n", MAXSIZE);
	printf("串长为%d 串空否: %d(1:是 0:否)\n",StrLength(s1), EmptyString(s1));
	printf("s1: ");
	StrPrint(s1);
	StrCopy(s2, s1);
	printf("拷贝s1生成s2为: ");
	StrPrint(s2);
	printf("\n");
	
	printf("Let string s2 = 'efghijk'\n");
	i = StrAssign(s2, "efghijk");
	printf("s2: ");
	StrPrint(s2);
	if (!i)
		printf("串长度超过MAXSIZE(=%d)\n", MAXSIZE);
	i = StrCompare(s1, s2);
	if(i<0)
		s='<';
	else if(i==0)
		s='=';
	else
		s='>';
	printf("串s1 %c 串s2\n", s);
	printf("\n");
	
	i = Concat(t, s1, s2);
	printf("串s1联接串s2得到的串t为: ");
	StrPrint(t);
	if(i==FALSE)
		printf("串t有截断\n");
	ClearString(s1);
	printf("清为空串后,串s1为: ");
	StrPrint(s1);
	printf("s1串长为%d 串空否？%d(1:是 0:否)\n",StrLength(s1), EmptyString(s1));
	printf("\n");

	printf("求串t的子串, 请输入子串的起始位置n, 子串长度m: ");
	n = 2;
	m = 3;
	printf("%d,%d \n", n, m);
	i = SubString(s2, t, n, m);
	if(i)
	{
		printf("子串s2为: ");
		StrPrint(s2);
	}
	printf("从串t的第n个字符起,删除m个字符，请输入n, m: ");
	n = 4;
	m = 2;
	printf("%d,%d \n", n, m);
	StrDelete(t, n, m);
	printf("删除后的串t为: ");
	StrPrint(t);
	printf("\n");
	
	i = StrLength(s2)/2;
	StrInsert(s2, i, t);
	printf("在串s2的第%d个字符之前插入串t后,串s2为:\n", i);
	StrPrint(s2);
	i = Index(s2,t,1);
	printf("s2的第%d个字母起和t第一次匹配\n", i);
	SubString(t, s2, 1, 1);
	printf("从第1个位置起往后取1位后, 串t为：");
	StrPrint(t);
	Concat(s1,t,t);
	printf("将t与t连接得串s1为：");
	StrPrint(s1);
	Replace(s2,t,s1);
	printf("用串s1取代串s2中和串t相同的不重叠的串后,串s2为: ");
	StrPrint(s2);
	
	return 0;
}






