#include<stdio.h>
int with_array(int num)
{
	int i;
	int a[num];
	a[0] = 0;
	a[1] = 1;
	printf("%d ", a[0]);
	printf("%d ", a[1]);
	for(i=2; i<num; i++)
	{
		a[i] = a[i-1] + a[i-2];
		printf("%d ", a[i]);
	}
	return 0;
}
int Fbi(int i)
{
	if (i < 2)
		return i==0?0:1;
	return Fbi(i-1)+Fbi(i-2);
}

int with_recursion(int num)
{
	int i;
	printf("递归显示斐波那契数列: \n");
	for(i=0; i<num; i++)
		printf("%d ", Fbi(i));
	return 0;
}

int main(void)
{
	int n;
	printf("Enter number to look: ");
	scanf("%d", &n);
	
	printf("With_array to look:\n");
	with_array(n);
	printf("\n");
	printf("With_recursion to look:\n");
	with_recursion(n);
	
	return 0;
}

