#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<io.h> 
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10000 	//排序数组最大个数
#define MAX_LENGTH_INSERT_SORT 7	//用于快速排序时判断是否选用插入排序阈值
#define N 9

typedef int Status;

typedef struct
{
	int r[MAXSIZE+1];	//存储要排序数组, r[0]用作哨兵/临时变量
	int length;			//记录顺序表长度
}SqList;

//交换L中数组r下标i和j的值;
void Swap(SqList *L, int i, int j)
{
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}
//打印数据;
void Print(SqList L)
{
	int i;
	for(i=1; i<L.length; i++)
		printf("%d ", L.r[i]);
	printf("%d ", L.r[i]);
	printf("\n");
}

//冒泡排序(初级);
void BubbleSort0(SqList *L)
{
	int i, j;
	for(i=1; i<L->length; i++)
	{
		for(j=i+1; j<=L->length; j++)
		{
			if(L->r[i]>L->r[j])
				Swap(L, i, j);
		}
	}
}
//冒泡排序;
void BubbleSort(SqList *L)
{
	int i, j;
	for(i=1; i<L->length; i++)
	{
		for(j=L->length-1; j>=i; j--)
		{
			if(L->r[i]>L->r[j+1])
			Swap(L, i, j+1);
		}
	}
}
//冒泡排序(改进);
void BubbleSort2(SqList *L)
{
	int i, j;
	Status flag = TRUE;
	for(i=1; i<L->length && flag; i++)
	{
		flag = FALSE;			//初始化flag
		for(j=L->length-1; j>=i; j--)
		{
			if(L->r[j]>L->r[j+1])
			{
				Swap(L, j, j+1);
				flag = TRUE;	//若有数据交换, 则flag为FALSE
			}
		}
	}
}

//简单选择排序;
void SelectSort(SqList *L)
{
	int i, j, min;
	for(i=1; i<L->length; i++)
	{
		min = i;
		for(j=i+1; j<=L->length; j++)
		{
			if(L->r[min]>L->r[j])
				min = j;
		}
		if(i!=min)				//说明找到了最小值, 则交换
			Swap(L, i, min);
	}
}

//直接插入排序;
void InsertSort(SqList *L)
{
	int i, j;
	for(i=2; i<=L->length; i++)
	{
		if(L->r[i]<L->r[i-1])
		{	//将L->r[i]插入有序子表
			L->r[0] = L->r[i];			//设置哨兵
			for(j=i-1; L->r[j]>L->r[0]; j--)
				L->r[j+1] = L->r[j];	//记录后移
			L->r[j+1] = L->r[0];		//插入到正确的位置
		}
	}
}

//希尔排序;
void ShellSort(SqList *L)
{
	int i, j, k=0;
	int increment = L->length;
	do{
		increment = increment/3+1;	//增量序列
		for(i=increment+1; i<=L->length; i++)
		{
			if(L->r[i]<L->r[i-increment])
			{	//需将L->r[i]插入有序增量子表
				L->r[0] = L->r[i];	//暂存在L->r[0]中
				for(j=i-increment; j>0&&L->r[0]<L->r[j]; j-=increment)
					L->r[j+increment] = L->r[j];	//记录后移, 查找插入位置
				L->r[j+increment] = L->r[0];		//插入
			}
		}
		printf("	第%d遍排序结果: ", ++k);
		Print(*L);
	}while(increment>1);
}

//堆调整;
void HeapAdjust(SqList *L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	for(j=2*s; j<=m; j*=2)	//沿关键字较大的孩子结点向下筛选
	{
		if(j<m && L->r[j]<L->r[j+1])
			++j;			//j为关键字中较大的记录的下标
		if(temp >=L->r[j])
			break;			//rc应插入在位置s上
		L->r[s] = L->r[j];
		s = j;
	}
	L->r[s] = temp;			//插入
}

//堆排序;
void HeapSort(SqList *L)
{
	int i;
	for(i=L->length/2; i>0; i--)
		HeapAdjust(L, i, L->length);
	for(i=L->length; i>1; i--)
	{
		Swap(L, 1, i);	//堆顶记录和当前未经排序子序列的最后1个记录交换
		HeapAdjust(L, 1, i-1);
	}
}

//归并调整, 将有序SR[i~m]和SR[m+1~n]归并为有序TR[i~n];
void Merge(int SR[], int TR[], int i, int m, int n)
{
	int j, k, l;
	for(j=m+1,k=i; i<=m&&j<=n; k++)		//将SR中记录由小到大并入TR
	{
		if(SR[i]<SR[j])
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	}
	if(i<=m)
	{
		for(l=0; l<=m-i; l++)
			TR[k+l] = SR[i+l];			//将剩余的SR[i~m]复制到TR
	}
	if(j<=n)
	{
		for(l=0; l<=n-j; l++)
			TR[k+l] = SR[j+l];			//将剩余的SR[j~n]复制到TR
	}
}

//归并排序(递归), 将SR[s~t]归并排序为TR1[s~t];
void MSort(int SR[], int TR1[], int s, int t)
{
	int m;
	int TR2[MAXSIZE+1];
	if(s==t)
		TR1[s] = SR[s];
	else
	{
		m = (s+t)/2;		//将SR[s~t]平分为SR[s~m]和SR[m+1~t]
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m+1, t);
		Merge(TR2, TR1, s, m, t);	//将TR2[s~m]和TR2[m+1~t]归并到TR1[s~t]
	}
}

//归并排序(递归);
void MergeSort(SqList *L)
{
	MSort(L->r, L->r, 1, L->length);
}

//归并调整, 将SR[]中相邻长度为s的子序列两两归并到TR[];
void MergePass(int SR[], int TR[], int s, int n)
{
	int i = 1;
	int j;
	while(i<=n-2*s+1)
	{	//两两归并
		Merge(SR, TR, i, i+s-1, i+2*s-1);
		i = i+2*s;
	}
	if(i<n-s+1)		//归并最后2个序列
		Merge(SR, TR, i, i+s-1, n);
	else			//若只剩单个子序列
		for(j=i; j<=n; j++)
			TR[j] = SR[j];
}

//归并排序(非递归);
void MergeSort2(SqList *L)
{
	int* TR = (int*)malloc(L->length * sizeof(int));
	int k = 1;
	while(k<=L->length)
	{
		MergePass(L->r, TR, k, L->length);
		k = 2*k;		//子序列长度加倍
		MergePass(TR, L->r, k, L->length);
		k = 2*k;		//子序列长度加倍
	}
}

//选取1个关键字作为枢轴, 并返回其位置;
int Partition(SqList *L, int low, int high)
{	//交换顺序表L中子表的记录, 使枢轴记录到位并返回其位置;
	int pivotkey;
	
	pivotkey = L->r[low];		//用第1个记录作为枢轴记录
	while(low<high)				//从表的两端交替向中间扫描
	{
		while(low<high && L->r[high]>=pivotkey)
			high--;
		Swap(L, low, high);		//将比枢轴记录小的记录交换到低端
		while(low<high && L->r[low]<=pivotkey)
			low++;
		Swap(L, low, high);		//将比枢轴记录大的记录交换到高端
	}
	return low;		//返回枢轴所在位置
}

//对顺序表L中的子序列L->r[low~high]作快速排序;
void QSort(SqList *L, int low, int high)
{
	int pivot;
	if(low<high)
	{
		pivot = Partition(L, low, high);
		QSort(L, low, pivot-1);		//对低子表递归排序
		QSort(L, pivot+1, high);	//对高子表递归排序
	}
}

//快速排序(递归);
void QuickSort(SqList *L)
{
	QSort(L, 1, L->length);
}

//优化选取枢轴及不必要的交换;
int Partition1(SqList *L, int low, int high)
{	//交换顺序表L中子表的记录, 使枢轴记录到位并返回其位置;
	int pivotkey;
	
	int m = low + (high-low)/2;	//计算数组中间元素的下标
	if(L->r[low]>L->r[high])
		Swap(L, low, high);		//交换左端和右端数据, 保证左端较小
	if(L->r[m]>L->r[high])
		Swap(L, high, m);		//交换中间和右端数据, 保证中间较小
	if(L->r[m]>L->r[low])
		Swap(L, m, low);		//交换中间和左端数据, 保证左端较小
	pivotkey = L->r[low];	//用子表的第1个记录作为枢轴记录
	L->r[0] = pivotkey;		//将枢轴关键字备份到r[0]
	while(low<high)				//从表的两端交替向中间扫描
	{
		while(low<high && L->r[high]>=pivotkey)
			high--;
		Swap(L, low, high);		//将比枢轴记录小的记录交换到低端
		while(low<high && L->r[low]<=pivotkey)
			low++;
		Swap(L, low, high);		//将比枢轴记录大的记录交换到高端
	}
	L->r[low] = L->r[0];
	return low;		//返回枢轴所在位置
}

//尾递归优化;
void QSort1(SqList *L, int low, int high)
{
	int pivot;
	if((high-low)>MAX_LENGTH_INSERT_SORT)
	{
		pivot = Partition(L, low, high);
		QSort(L, low, pivot-1);		//对低子表递归排序
		QSort(L, pivot+1, high);	//对高子表递归排序
	}
	else
		InsertSort(L);		//当(high-low)<=常数时用直接插入排序
}
void QSort2(SqList *L, int low, int high)
{
	int pivot;
	if((high-low)>MAX_LENGTH_INSERT_SORT)
	{
		while(low<high)
		{
			pivot = Partition1(L, low, high);
			QSort(L, low, pivot-1);		//对低子表递归排序
			low = pivot+1;				//尾递归
		}
	}
	else
		InsertSort(L);		//当(high-low)<=常数时用直接插入排序
}

//快速排序(优化);
void QuickSort1(SqList *L)
{
	QSort1(L, 1, L->length);
}

void QuickSort2(SqList *L)
{
	QSort2(L, 1, L->length);
}

int main(void)
{
	int i;
	int d[N] = {50,10,90,30,70,40,80,60,20};
	SqList l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11;
	
	for(i=0; i<N; i++)
		l0.r[i+1]=d[i];
	l0.length=N;
	l1=l2=l3=l4=l5=l6=l7=l8=l9=l10=l11=l0;
	printf("排序前:\n");
	Print(l0);
	
	printf("初级冒泡排序:\n");
	BubbleSort0(&l0);
	Print(l0);
	
	printf("冒泡排序:\n");
	BubbleSort(&l1);
	Print(l1);
	
	printf("改进冒泡排序:\n");
	BubbleSort2(&l2);
	Print(l2);
	
	printf("选择排序:\n");
	SelectSort(&l3);
	Print(l3);
	
	printf("直接插入排序:\n");
	InsertSort(&l4);
	Print(l4);
	
	printf("希尔排序:\n");
	ShellSort(&l5);
	Print(l5);
	
	printf("堆排序:\n");
	HeapSort(&l6);
	Print(l6);
	
	printf("归并排序（递归）:\n");
	MergeSort(&l7);
	Print(l7);
	
	printf("归并排序（非递归）:\n");
	MergeSort2(&l8);
	Print(l8);
	
	printf("快速排序:\n");
	QuickSort(&l9);
	Print(l9);
	
	printf("改进快速排序:\n");
	QuickSort1(&l10);
	Print(l10);
	
	printf("改进快速排序(尾递归):\n");
	QuickSort2(&l11);
	Print(l11);
}
