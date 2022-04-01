#include<iostream>
#include<vector>
using namespace std;
#include "Sales_data.h"
#include "Screen.h"

class Person
{
private:
	string m_Name;
	string m_Address;
public:
	string get_Name() const { return m_Name; }
	string get_Address() const { return m_Address; }
};

int main()
{
	/*cout << "请输入交易记录: " << endl;
	Sales_data total(cin);
	if (read(cin, total))
	{
		Sales_data trans(cin);
		while (read(cin, total))
		{
			if (total.isbn() == trans.isbn())
				total = add(total, trans);
			else
			{
				print(cout, total);
				cout << endl;
				total = trans;
			}
		}
		print(cout, total);
		cout << endl;
	}
	else {
		cerr << "No data!" << endl;
		return -1;
	}*/

	/*Screen myScreen(5, 5, 'X');
	myScreen.move(4, 0).set('#').display(cout);
	cout << endl;
	myScreen.display(cout);
	cout << endl;*/

	return 0;
}