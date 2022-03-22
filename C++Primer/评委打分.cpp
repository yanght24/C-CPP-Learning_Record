#include<iostream>
#include<algorithm>
#include<vector>
#include<deque>
#include<ctime>
using namespace std;

class Person
{
public:
	Person(string name, int score)
	{
		this->m_Name = name;
		this->m_Score = score;
	}
	
	string m_Name;
	int m_Score;
};

void CreatePerson(vector<Person>&v)
{
	string nameSeed = "ABCDE";
	for(int i = 0; i < 5; i++)
	{
		string name = "选手";
		name += nameSeed[i];
		
		int score = 0;
		Person p(name, score);
		v.push_back(p);
	}
}

void SetScore(vector<Person>&v)
{
	for(vector<Person>::iterator it = v.begin(); it < v.end(); it++)
	{
		deque<int>d;
		for(int i = 0; i < 10; i++)
		{
			int score = rand()%40+1 + 60;		//60~100
			d.push_back(score);
		}
		//排序
		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();
		//平均分
		int sum = 0;
		for(deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += *dit;
		}
		
		int avg = sum/d.size();
		//将分数赋给选手
		it->m_Score = avg;
	}
}

void ShowScore(vector<Person>&v)
{
	for(vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "姓名: " << it->m_Name << endl;
		cout << "分数: " << it->m_Score << endl;
	}
}

int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));
	
	//1. 创建5名选手
	vector<Person>v;
	CreatePerson(v);
	
	//2. 给5名选手打分
	SetScore(v);
	
	//3. 显示最后分数
	ShowScore(v);
}
