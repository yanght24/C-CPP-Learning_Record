#pragma once
#include<iostream>
using namespace std;

class Sales_data
{
	friend Sales_data add(const Sales_data& lhs, const Sales_data& rhs);
	friend istream& read(istream& is, Sales_data& item);
	friend ostream& print(ostream& os, const Sales_data& item);

public:
	Sales_data() = default;
	Sales_data(const string& s, unsigned n, double p) :
		bookNo(s), unit_sold(n), revenue(p* n) {}
	Sales_data(const string &s):bookNo(s) {}
	Sales_data(istream&) { read(cin, *this); }

	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

private:
	string bookNo;				//ISBN
	unsigned unit_sold = 0;		//销售量
	double sellingprice = 0.0;	//零售价
	double saleprice = 0.0;		//实售价
	double revenue = 0.0;		//售卖额
	double discount = 0.0;		//折扣
};


Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

ostream &print(ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.unit_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

//输入的交易信息包括ISBN, 售出总数, 售出价格
istream &read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.unit_sold >> price;
	item.revenue = price * item.unit_sold;
	return is;
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	unit_sold += rhs.unit_sold;
	revenue += rhs.revenue;
	saleprice = (saleprice * unit_sold + rhs.saleprice * rhs.unit_sold) /
				(unit_sold + rhs.unit_sold);
	if (saleprice != 0)
		discount = saleprice / sellingprice;
	return *this;
}

double Sales_data::avg_price() const
{
	if (unit_sold)
		return revenue / unit_sold;
	else
		return 0;
}