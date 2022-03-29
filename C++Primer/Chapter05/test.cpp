#include<iostream>
#include<stdexcept>
#include<vector>
using namespace std;

int main()
{
	int a = 0, b = 0;
	while (cin >> a >> b)
	{
		try
		{
			if (b == 0)
				throw runtime_error("除数不能为0");
			cout << "a / b = " << a / b << endl;
		}
		catch (runtime_error err)
		{
			cout << err.what() << endl;
			cout << "\nTry Again? Enter y or n" << endl;
			char ch = 0;
			cin >> ch;
			if (ch != 'y' && ch != 'Y')
				break;
		}
	}

	return 0;
}