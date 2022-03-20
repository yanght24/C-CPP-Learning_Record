#include<iostream>
using namespace std;

class Calculator
{
public:
	int get_result(string oper)
	{
		if (oper == "+")
		{
			return m_Num1+m_Num2;
		}
		else if (oper == "-")
		{
			return m_Num1-m_Num2;
		}
		else if (oper == "*")
		{
			return m_Num1*m_Num2;
		}
	}
	
	int m_Num1;
	int m_Num2;
};

void test01()
{
	Calculator c;
	c.m_Num1 = 10;
	c.m_Num2 = 20;
	
	cout << c.m_Num1 << " + " << c.m_Num2 << " = " << c.get_result("+") << endl;
	cout << c.m_Num1 << " - " << c.m_Num2 << " = " << c.get_result("-") << endl;
	cout << c.m_Num1 << " * " << c.m_Num2 << " = " << c.get_result("*") << endl;
}

class CalAbstract
{
public:
	virtual int get_result()
	{
		return 0;
	}
	
	int m_Num1;
	int m_Num2;
};

class AddCalculator : public CalAbstract
{
public:
	int get_result()
	{
		return m_Num1+m_Num2;
	}
};

class SubCalculator : public CalAbstract
{
public:
	int get_result()
	{
		return m_Num1-m_Num2;
	}
};

class MulCalculator : public CalAbstract
{
public:
	int get_result()
	{
		return m_Num1*m_Num2;
	}
};

void test02()
{
	CalAbstract *abc = new AddCalculator;
	abc->m_Num1 = 15;
	abc->m_Num2 = 25;
	cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->get_result() << endl;
	delete abc;
	
	abc = new SubCalculator;
	abc->m_Num1 = 15;
	abc->m_Num2 = 25;
	cout << abc->m_Num1 << " - " << abc->m_Num2 << " = " << abc->get_result() << endl;
	delete abc;
	
	abc = new MulCalculator;
	abc->m_Num1 = 15;
	abc->m_Num2 = 25;
	cout << abc->m_Num1 << " * " << abc->m_Num2 << " = " << abc->get_result() << endl;
	delete abc;
}

int main()
{
	//test01();
	test02();
	
	return 0;
}
