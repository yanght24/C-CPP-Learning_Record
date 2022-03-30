#include<iostream>
using namespace std;
#include "Chapter6.h"

int main(int argc, char *argv[])
{
	//cout << "10! = " << factorial(10) << endl;

	//cout << test01(5) << endl;	//6
	//cout << test01(5) << endl;	//7

	/*int a = 10, b = 20;
	swap(&a, &b);
	cout << "a = " << a << "  " << "b = " << b << endl;
	swap2(a, b);
	cout << "a = " << a << "  " << "b = " << b << endl;*/

	/*string s;
	cin >> s;
	cout << find_upper(s) << endl;
	to_lower(s);
	cout << s << endl;*/

	/*int num1 = 10, num2 = 20;
	int *p = &num1, *q = &num2;
	cout << find_bigger(num1, &num2) << endl;
	cout << p << endl;
	cout << q << endl;
	swap_ptr(p, q);
	cout << p << endl;
	cout << q << endl;*/

	/*for (int i = 0; i != argc; ++i)
	{
		cout << "argc[" << i << "]: " << argv[i] << endl;
	}*/

	
	//cout << add_init({ 1,2,3,4,5 }) << endl;
	//cout << add_init({ 6,7,8,9,10 }) << endl;

	/*string s1 = "abcd";
	string s2 = "abcdef";
	cout << str_subrange(s1, s2) << endl;*/

	/*vector<int>v = { 1,3,5,7,9,11,13,15 };
	print_rec(v, 0);*/

	//cout << isShorter("abcd", "ab") << endl;

	decltype (addf)* p1 = addf, * p2 = subf, * p3 = mulf, * p4 = divf;
	vector<decltype(addf)*>v = { p1,p2,p3,p4 };
	for (auto i : v)
	{
		cout << i << endl;
	}

	return 0;
}