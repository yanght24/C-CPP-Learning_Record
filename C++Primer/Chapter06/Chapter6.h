#pragma once
#include<iostream>
#include<vector>
#include<initializer_list>
using namespace std;

int factorial(int val);	//6.3
int test01(int val);	//6.6测试形参, 局部变量, 局部静态变量的使用
void swap(int *val1, int *val2);	//6.10
void swap2(int &val1, int &val2);	//6.10
bool find_upper(const string s);	//6.17
void to_lower(string& s);			//6.17
int find_bigger(const int val1, const int *val2);	//6.21
void swap_ptr(int *&val1, int *&val2);				//6.22
int add_init(initializer_list<int>lint);			//6.27
bool str_subrange(const string& str1, const string& str2);	//6.30
void print_rec(const vector<int>v, unsigned index);			//6.33

//string(*func1(int i))[10];		//6.36 + 6.37
//typedef string arr[10];			//普通声明返回数组引用的函数
//using arr = string[10];	//等价于
//arr &func2();					//使用类型别名
//auto func3()->string(&)[10];	//使用尾置返回
//string str[10];
//decltype(str) &func4();			//使用decltype

inline bool isShorter(const string& s1, const string& s2);	//6.44
inline bool isShorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

int addf(int a, int b);				//6.55
int subf(int a, int b);
int mulf(int a, int b);
int divf(int a, int b);