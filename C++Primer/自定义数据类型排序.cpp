#include<iostream>
#include<algorithm>
#include<list>
using namespace std;

class Person
{
public:
	Person(string name, int age, int height)
	{
		this->m_Name = name;
		this->m_Age = age;
		this->m_Height = height;
	}
	
	string m_Name;
	int m_Age;
	int m_Height;
};

bool comparePerson(Person &p1, Person &p2)
{
	//按照年龄升序, 年龄相同身高降序
	if(p1.m_Age == p2.m_Age)
	{
		return p1.m_Height > p2.m_Height;
	}
	return p1.m_Age < p2.m_Age;
}

void test01()
{
	//创建容器
	list<Person>L;		
	
	//准备数据
	Person p1("刘一", 35, 175);
	Person p2("曹二", 45, 180);
	Person p3("孙三", 40, 170);
	Person p4("赵四", 25, 190);
	Person p5("张五", 35, 160);
	Person p6("关六", 35, 200);
	
	//插入数据
	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);
	
	for(list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名: " << (*it).m_Name << "  "
			<< "年龄: " << it->m_Age << "  "
			<< "身高: " << it->m_Height << endl;
	}
	
	//排序
	cout << "___________________________________" << endl;
	cout << "排序后: " << endl;
	L.sort(comparePerson); 	//自定义数据类型排序要指定规则
	for(list<Person>::iterator it = L.begin(); it != L.end(); it++)
	{
		cout << "姓名: " << (*it).m_Name << "  "
		<< "年龄: " << it->m_Age << "  "
		<< "身高: " << it->m_Height << endl;
	}
}

int main()
{
	test01();
	
	return 0;
}
