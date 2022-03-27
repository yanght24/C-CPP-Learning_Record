#pragma once
#include<iostream>
using namespace std;

struct Sales_data
{
	string bookNo;				//ISBN
	unsigned unit_sold = 0;		//销售量
	double sellingprice = 0.0;	//零售价			、、
	double saleprice = 0.0;		//实售价
	double revenue = 0.0;		//售卖额
	double discount = 0.0;		//折扣
};