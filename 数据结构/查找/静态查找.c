#include<stdio.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 	//存储空间初始分配量

int F[100];			//斐波那契数列

typedef int Status;		//函数结果状态代码

//使用顺序表查找算法 (无哨兵);
Status Sequential_Search(int *a, int n, int key)
{	
	int i;
	for(i=1; i<=n; i++)
	{
		if(a[i]==key)
			return i;
	}
	return OK;
}

//使用顺序表查找算法 (有哨兵);
Status Sequential_Search2(int *a, int n, int key)
{
	int i;
	a[0] = key;			//设置a[0]为关键字值, 作为哨兵
	i = n;				//从数组尾部开始
	while(a[i]!=key)
	{
		i--;
	}
	return OK;
}

//折半查找;
Status Binary_Search(int *a, int n, int key)
{
	int low, high, mid;
	low = 1;
	high = n;
	while(low<=high)
	{
		mid = (low+high)/2;
		if(key<a[mid])
			high = mid-1;
		else if(key>a[mid])
			low = mid+1;
		else
			return mid;
	}
	return OK;
}

//插值查找;		mid=(low+high)/2 --> low+(high-low)/2 ---> low+[(key-a[low])(high-low)/(a[high]-a[low])]
Status Interpolation_Search(int *a, int n, int key)
{
	int low, high, mid;
	low = 1;
	high = n;
	while(low<=high)
	{
		mid = low+(high-low)*(key-a[low])/(a[high]-a[low]);		//进行插值
		if(key<a[mid])
			high = mid-1;
		else if(key>a[mid])
			low = mid+1;
		else
			return mid;
	}
	return OK;
}

//斐波那契查找(利用黄金分割原理);
Status Fibonacci_Search(int *a, int n, int key)
{
	int low, high, mid, i, k;
	low = 1;
	high = n;
	k = 0;
	while(n>F[k]-1)		//计算n处于斐波那契数列的位置
		k++;
	for(i=n; i<F[k]-1; i++)		//将a数列中缺少的数值补满
		a[i] = a[n];
	while(low<=high)
	{
		mid = low+F[k-1]-1;
		if(key<a[mid])			//新范围是第low~第mid个
		{						//此时, 范围个数为F[k-1]-1个
			high = mid-1;
			k = k-1;
		}
		else if(key>a[mid])		//新范围是第m+1~第high个
		{						//此时, 范围个数为F[k-2]-2个
			low = mid+1;
			k = k-2;
		}
		else
		{
			if(mid<=n)
				return mid;		//相等则说明mid即为查找到的位置
			else
				return n;		//mid>n说明是补全数值, 返回n
		}
	}
	return OK;
}

int main(void)
{
	int a[MAXSIZE+1], i, result;
	int arr[MAXSIZE] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};
	for(i=0; i<=MAXSIZE; i++)
	{
		a[i] = i;
	}
	result = Sequential_Search(a, MAXSIZE, MAXSIZE);
	printf("Sequential_Search:  %d \n", result);
	result = Sequential_Search2(a, MAXSIZE, MAXSIZE);
	printf("Sequential_Search2: %d \n", result);
	result = Binary_Search(arr, 10, 62);
	printf("Binary_Search: %d \n", result);
	result = Interpolation_Search(arr, 10, 62);
	printf("Interpolation_Search: %d \n", result);
	F[0] = 0;
	F[1] = 1;
	for(i=2; i<100; i++)
	{
		F[i] = F[i-1]+F[i-2];
	}
	result = Fibonacci_Search(arr, 10, 62);
	printf("Fibonacci_Search: %d \n", result);
	
	return 0;
}
