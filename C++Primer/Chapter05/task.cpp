/*
5.14
检测输入字符串中出现次数最多的单词及其出现次数
{
	string nowstring, prestring, maxstring;
	int cnt = 1, maxCnt = 0;
	while (cin >> nowstring)
	{
		if (nowstring == prestring)
			++cnt;
		if (cnt > maxCnt)
		{
			maxCnt = cnt;
			maxstring = nowstring;
		}
		else
			cnt = 1;
		prestring = nowstring;
	}
	if (maxCnt > 1)
		cout << maxstring << " " << maxCnt << endl;
	else
}

5.17
检查两个vector<int>其中一个是否是另一个的前缀
{
	vector<int>v1 = { 0,1,1,2 };
	vector<int>v2 = { 0,1,1,2,3,5,8 };
	auto it1 = v1.cbegin();
	auto it2 = v2.cbegin();

	while (it1 != v1.cend() && it2 != v2.cend())
	{
		if (*it1 != *it2)
		{
			cout << "v1和v2不存在前缀关系." << endl;
			break;
		}
		++it1;
		++it2;
	}
	if (it1 == v1.cend())
		cout << "v1是v2的前缀";
	if (it2 == v2.cend())
		cout << "v2是v1的前缀";
}
5.20
读取string直至出现连续两个相同的单词或读完
string nowString, preString;
	bool no_same = true;
	while (cin >> nowString)
	{
		if (nowString == preString)
		{
			no_same = false;
			cout << "the next same is: " << nowString << endl;
			break;
		}
		preString = nowString;
	}
	if (no_same)
		cout << "No next same." << endl;
5.21
添加检测条件, 单词是否以大写字母开头
if(isupper(nowString[0]));

5.25
使用try-catch结构实现对两个整数相除的判断
{
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
}
*/