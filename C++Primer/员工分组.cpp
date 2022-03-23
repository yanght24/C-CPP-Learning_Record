#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<map>
using namespace std;

#define CEHUA 0
#define MEISHU 1
#define YANFA 2

class Worker
{
public:
	
	
	string m_Name;
	int m_Salary;
};

void CreateWorker(vector<Worker>&v)
{
	string nameSeed = "ABCDEFGHIJ";
	for(int i = 0; i < 10; i++)
	{
		Worker worker;
		worker.m_Name = "员工";
		worker.m_Name += nameSeed[i];
		worker.m_Salary = rand()%10000 + 10000;
		v.push_back(worker);
	}
}

void SetGroup(vector<Worker>&v, multimap<int, Worker>&m)
{
	for(vector<Worker>::iterator it = v.begin(); it != v.end(); it++)
	{	
		//产生随机部门分组
		int deptId = rand()%3;
		//将员工插入到分组中
		m.insert(make_pair(deptId, *it));
	}
}
 
void ShowWorker(multimap<int, Worker>&m)
{
	cout << "策划: " << endl;
	multimap<int, Worker>::iterator pos = m.find(CEHUA);
	int count = m.count(CEHUA);
	int index = 0;
	for( ; pos!=m.end()&&index<count; pos++, index++)
	{
		cout << "姓名: " << pos->second.m_Name << "  "
			<< "工资: " << pos->second.m_Salary << endl;
	}
	cout << "-----------------------------------------";
	cout << "美术: " << endl;
	pos = m.find(MEISHU);
	count = m.count(MEISHU);
	index = 0;
	for( ; pos!=m.end()&&index<count; pos++, index++)
	{
		cout << "姓名: " << pos->second.m_Name << "  "
		<< "工资: " << pos->second.m_Salary << endl;
	}
	cout << "-----------------------------------------";
	cout << "研发: " << endl;
	pos = m.find(YANFA);
	count = m.count(YANFA);
	index = 0;
	for( ; pos!=m.end()&&index<count; pos++, index++)
	{
		cout << "姓名: " << pos->second.m_Name << "  "
		<< "工资: " << pos->second.m_Salary << endl;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	//1. 创建员工
	vector<Worker>vWorker;
	CreateWorker(vWorker);
	
	//2. 分组
	multimap<int, Worker>mWorker;
	SetGroup(vWorker, mWorker);
	
	//3. 显示
	ShowWorker(mWorker);
}
