#include<iostream>
#include "Sales_item.h"
using namespace std;

/*
按照题目要求是将每个ISBN的记录聚在一起
但答案无法实现该要求, 只能输入后即打印
可以添加Sales_item数组存储ISBN相同的记录
待输入完成后, 遍历数组打印结果
*/

int main()
{
	Sales_item total, trans;

	if (cin >> total)
	{
		while (cin >> trans)
		{
			if (total.isbn() == trans.isbn())
				total += trans;
			else
			{
				cout << total << endl;
				total = trans;
			}
		}
		cout << total << endl;
	}
	else
	{
		cout << "No data?!" << endl;
		return -1;
	}
	return 0;
}