#include<iostream>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<string>
#include<vector>
using namespace std;

istream& func(istream& ist)
{
	string v;
	while (ist >> v, !ist.eof())
	{
		if (ist.bad())
			throw runtime_error("IO流错误");
		if (ist.fail())
		{
			cerr << "数据错误, 请重试: " << endl;
			ist.clear();
			ist.ignore(100, '\n');
			continue;
		}
		cout << v << endl;
	}
	ist.clear();
	return ist;
}

struct PersonInfo
{
	string name;
	vector<string> phones;
};

string format(const string& s) { return s; }

bool valid(const string& s)
{
	return true;
}

int main(int argc, char* argv[])
{
	//--------------------8.4--------------------
	/*ifstream ifs("text.txt");
	if (!ifs)
	{
		cerr << "无法打开文件！" << endl;
		return -1;
	}
	string line;
	vector<string>v;
	while (ifs >> line)
		v.push_back(line);
	ifs.close();

	for (auto c : v)
		cout << c << endl;*/

	//--------------------8.9--------------------
	/*ostringstream osg;
	osg << "C++ Primer 第五版" << endl;
	istringstream ist(osg.str());
	func(ist);*/

	//--------------------8.10--------------------
	/*ifstream ifs("text.txt");
	if (!ifs)
	{
		cerr << "无法打开文件！" << endl;
		return -1;
	}
	string line;
	vector<string>words;
	while (getline(ifs, line))
	{
		words.push_back(line);
	}
	ifs.close();
	for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it)
	{
		istringstream line_str(*it);
		string word;
		while (line_str >> word)
			cout << word << " ";
		cout << endl;
	}*/

	//--------------------8.13--------------------
	string line, word;
	vector<PersonInfo>people;
	istringstream record;

	if (argc != 2)
	{
		cerr << "请给出文件名" << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "无法打开输入文件" << endl;
		return -1;
	}
	while (getline(in, line))
	{
		PersonInfo info;		//创建一个保存此记录数据的对象
		record.clear();			//重复使用字符串流时, 每次都要调用clear
		record.str(line);		//将记录绑定到刚读入的行
		record >> info.name;	//读取名字
		while (record >> word)	//读取电话号码
			info.phones.push_back(word);
		people.push_back(info);
	}
	ostringstream os;
	for (const auto& entry : people)
	{
		ostringstream formatted, badNums;	//每个循环步创建的对象
		for (const auto& nums : entry.phones)
		{
			if (!valid(nums))
				//将数的字符串形式存入
				badNums << " " << nums;
			else
				//将格式化的字符串 "写入"
				formatted << " " << format(nums);
		}
		if (badNums.str().empty())
			os << entry.name << " " << formatted.str() << endl;
		else
			cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() << endl;
	}
	cout << os.str() << endl;

	return 0;
}