/*
3.17
读入字符串, 将字符串中的每个单词都改为大写形式
{
	string word;
	vector<string>str;

	while(cin >> word)
	{
		str.push_back(word);
	}
	for(auto &s : str)
	{
		for(auto &c : s)
		{
			c = toupper(c);
		}
		cout << s << endl;
	}
}

3.20
读入一组整数, 将每队相邻/首尾相对的整数和输出
{
	void get_nextTow()
{
	int num;
	vector<int>arr;

	while (cin >> num)
	{
		arr.push_back(num);
	}
	if (arr.size() == 0)
	{
		cout << "No data!" << endl;
		return;
	}
	else
	{
		for (decltype(arr.size())i = 0; i < arr.size() - 1; i += 2)
		{
			//求相邻两项和
			cout << arr[i] + arr[i + 1] << " ";
			//每行输出5个数
			if ((i + 2) % 10 == 0)
			{
				cout << endl;
			}
		}
	}
	//奇数单独处理
	if (arr.size() % 2 != 0)
	{
		cout << arr[arr.size() - 1];
	}
}

void get_opposeTwo()
{
	int num;
	vector<int>arr;

	while (cin >> num)
	{
		arr.push_back(num);
	}
	if (arr.size() == 0)
	{
		cout << "No data!" << endl;
		return;
	}
	else
	{
		for (decltype(arr.size())i = 0; i < arr.size() - 1; i += 2)
		{
			//求相邻两项和
			cout << arr[i] + arr[arr.size() - 1 - i] << " ";
			//每行输出5个数
			if ((i + 2) % 10 == 0)
			{
				cout << endl;
			}
		}
	}
	//奇数单独处理
	if (arr.size() % 2 != 0)
	{
		cout << arr[arr.size() / 2];
	}
}
}

3.25
用迭代器改写用下标实现的分数段划分程序
{
	vector<unsigned>scores(11, 0);
	unsigned grade;
	while(cin >> grade)
	{
		if (grade <= 100)
			++scores[grade / 10];
	}

	vector<unsigned>scores(11, 0);
	auto it = scores.begin();
	unsigned grade;
	while (cin >> grade)
	{
		if (grade <= 100)
		{
			++* (it + grade / 10);
		}
	}
}

3.41
用整型数组初始化vector对象: 指明拷贝区域的首尾地址
{
	int arr[10] = { 0 };
	for (auto &val : arr)
	{
		val = rand() % 100;
		cout << val << " ";
	}
	cout << endl;
	vector<int>vInt(begin(arr), end(arr));
	for (auto val : vInt)
		cout << val << " ";
}
3.42
将vector对象拷贝给整型数组: 将vector对象的每个元素逐一赋值给数组
{
	vector<int>vInt;
	for (int i = 0; i != 10; i++)
	{
		vInt.push_back(i);
		cout << vInt[i] << " ";
	}
	cout << endl;
	int arr[10] = {0};
	auto it = vInt.begin();
	for (auto &val : arr)
	{
		val = *it;
		cout << val << " ";
		it++;
	}
}

3.43
用不同方式输出多维数组的值, 不用类型别名, auto, decltype
{
	constexpr size_t rowCnt = 3, colCnt = 4;
	int ia[rowCnt][colCnt] = { 0 };
	size_t cnt = 0;
	for (auto& row : ia)
	{
		for (auto& col : row)
		{
			col = cnt;
			++cnt;
		}
	}
	//使用范围for
	for (int (&row)[colCnt] : ia)
	{
		for (int &col : row)
		{
			cout << col << " ";
		}
		cout << endl;
	}
	cout << endl;
	//使用普通for, 用下标运算符
	for (int i = 0; i != rowCnt; i++)
	{
		for (int j = 0; j != colCnt; j++)
		{
			cout << ia[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	//使用普通for, 用指针
	for (int (*i)[colCnt] = ia; i != ia + rowCnt; i++)
	{
		for (int *j = *i; j != *i + colCnt; j++)
		{
			cout << *j << " ";
		}
		cout << endl;
	}
}

3.44
加用类型别名来代替循环控制变量的类型
{
	using int_array = int[colCnt];
	typedef int int_array[colCnt];
	for (int_array* i = ia; i != ia + rowCnt; i++)
	{
		for (int* j = *i; j != *i + colCnt; j++)
		{
			cout << *j << " ";
		}
		cout << endl;
	}
}

3.45
使用auto
{
	//使用范围for
	for (auto& row : ia)
	{
		for (auto& col : row)
		{
			cout << col << " ";
		}
		cout << endl;
	}
	cout << endl;
	//使用普通for, 用下标运算符
	for (auto i = 0; i != rowCnt; i++)
	{
		for (auto j = 0; j != colCnt; j++)
		{
			cout << ia[i][j] << " ";
		}
		cout << endl;
	}
	//使用普通for, 用指针
	for (auto i = ia; i != ia + rowCnt; i++)
	{
		for (auto j = *i; j != *i + colCnt; j++)
		{
			cout << *j << " ";
		}
		cout << endl;
	}
}
*/