/*
功能需求
1.添加联系人: 包括姓名, 性别, 年龄, 电话, 住址, 最多记录1000人
2.显示联系人: 显示出所有联系人信息
3.删除联系人: 按姓名删除指定联系人的信息
4.查找联系人: 按姓名查看指定联系人的信息
5.修改联系人: 按姓名重新修改联系人的信息
6.清空联系人: 清空通讯录中所有信息
0.退出通讯录: 退出当前使用的通讯录
*/
#include<iostream>
#include<string>
using namespace std;

#define MAX 1000

//联系人结构体;
struct Person
{
	string m_Name;
	int m_Sex;
	int m_Age;
	string m_Phone;
	string m_Addr;
};
//通讯录结构体;
struct Addressbook
{
	struct Person PersonArray[MAX];
	int m_Size;
};

//显示菜单;
void ShowMenu()
{
	cout << "**************************" << endl;
	cout << "*****  1.添加联系人  *****" << endl;
	cout << "*****  2.显示联系人  *****" << endl;
	cout << "*****  3.删除联系人  *****" << endl;
	cout << "*****  4.查找联系人  *****" << endl;
	cout << "*****  5.修改联系人  *****" << endl;
	cout << "*****  6.清空联系人  *****" << endl;
	cout << "*****  0.退出通讯录  *****" << endl;
	cout << "**************************" << endl;
}

//添加联系人;
void AddPerson(Addressbook *abs)
{
	if(abs->m_Size == MAX)
	{
		cout << "通讯录已满, 无法添加!" << endl;
		return;
	}
	else
	{
		
		cout << "请输入姓名: " << endl;
		string name;
		cin >> name;
		abs->PersonArray[abs->m_Size].m_Name = name;
		
		cout << "请输入性别: " << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int sex = 0;
		while(true)
		{
			cin >> sex;
			if(sex == 1 || sex == 2)
			{
				abs->PersonArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误, 请重新输入" << endl;
		}
		
		cout << "请输入年龄: " << endl;
		int age = 0;
		while(true)
		{
			cin >> age;
			if(age >= 0 && age <= 150)
			{
				abs->PersonArray[abs->m_Size].m_Age = age;
				break;
			}
			cout << "输入有误, 请重新输入" << endl;
		}
		
		cout << "请输入电话: " << endl;
		string phone;
		cin >> phone;
		abs->PersonArray[abs->m_Size].m_Phone = phone;
		
		cout << "请输入住址: " << endl;
		string address;
		cin >> address;
		abs->PersonArray[abs->m_Size].m_Addr = address;
			
		abs->m_Size++;
		cout << "添加成功" << endl;
		system("pause");
		system("cls");
	}
} 

//显示联系人;
void ShowPerson(Addressbook *abs)
{
	if(abs->m_Size == 0)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{
		for(int i = 0; i < abs->m_Size; i++)
		{
			cout << "姓名: " << abs->PersonArray[i].m_Name << "\t";
			cout << "性别: " << (abs->PersonArray[i].m_Sex==1 ? "男":"女") << "\t";
			cout << "年龄: " << abs->PersonArray[i].m_Age << "\t";
			cout << "电话: " << abs->PersonArray[i].m_Phone << "\t";
			cout << "住址: " << abs->PersonArray[i].m_Addr << endl;
		}
	}
	system("pause");
	system("cls"); 
}

//检测联系人是否存在;
int CheckPerson(Addressbook *abs, string name)
{
	for(int i = 0; i < abs->m_Size; i++)
	{
		if(abs->PersonArray[i].m_Name == name)
		{
			return i;
		}
	}
	return -1;
}

//删除联系人;
void DeletePerson(Addressbook *abs)
{
	cout << "请输入要删除的联系人: " << endl;
	string name;
	cin >> name;
	int ret = CheckPerson(abs, name);
	if(ret != -1)
	{
		for(int i = ret; i < abs->m_Size; i++)
		{
			abs->PersonArray[i] = abs->PersonArray[i+1];
		}
		abs->m_Size--;
		cout << "删除成功" << endl;
	}
	else
		cout << "查无此人" << endl;
	system("pause");
	system("cls");
}

//查找联系人;
void FindPerson(Addressbook *abs)
{
	cout << "请输入要查找的联系人: " << endl;
	string name;
	cin >> name;
	int ret = CheckPerson(abs, name);
	if(ret != -1)
	{
		cout << "姓名: " << abs->PersonArray[ret].m_Name << "\t";
		cout << "性别: " << (abs->PersonArray[ret].m_Sex==1 ? "男":"女") << "\t";
		cout << "年龄: " << abs->PersonArray[ret].m_Age << "\t";
		cout << "电话: " << abs->PersonArray[ret].m_Phone << "\t";
		cout << "住址: " << abs->PersonArray[ret].m_Addr << endl;
	}
	else
		cout << "查无此人" << endl;
	system("pause");
	system("cls");
}

//修改联系人;
void ModifyPerson(Addressbook *abs)
{
	cout << "请输入要修改的联系人: " << endl;
	string name;
	cin >> name;
	int ret = CheckPerson(abs, name);
	if(ret != -1)
	{
		cout << "请输入姓名: " << endl;
		string name;
		cin >> name;
		abs->PersonArray[abs->m_Size].m_Name = name;
		
		cout << "请输入性别: " << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int sex = 0;
		while(true)
		{
			cin >> sex;
			if(sex == 1 || sex == 2)
			{
				abs->PersonArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误, 请重新输入" << endl;
		}
		
		cout << "请输入年龄: " << endl;
		int age = 0;
		while(true)
		{
			cin >> age;
			if(age >= 0 && age <= 150)
			{
				abs->PersonArray[abs->m_Size].m_Age = age;
				break;
			}
			cout << "输入有误, 请重新输入" << endl;
		}
		
		cout << "请输入电话: " << endl;
		string phone;
		cin >> phone;
		abs->PersonArray[abs->m_Size].m_Phone = phone;
		
		cout << "请输入住址: " << endl;
		string address;
		cin >> address;
		abs->PersonArray[abs->m_Size].m_Addr = address;
		
		cout << "修改成功" << endl;
	}
	else
		cout << "查无此人" << endl;
	system("pause");
	system("cls");
}

//清空联系人;
void ClearPerson(Addressbook *abs)
{
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls");
}

int main(void)
{
	Addressbook abs;
	abs.m_Size = 0;
	
	int select = 0;
	
	while(true)
	{
		ShowMenu();
		
		cin >> select;
		switch(select)
		{
		case 1:		//1.添加联系人
			AddPerson(&abs);
			break;
		case 2:		//2.显示联系人
			ShowPerson(&abs);
			break;
		case 3:		//3.删除联系人
			DeletePerson(&abs);
			break;
		case 4:		//4.查找联系人
			FindPerson(&abs);
			break;
		case 5:		//5.修改联系人
			ModifyPerson(&abs);
			break;
		case 6:		//6.清空联系人
			ClearPerson(&abs);
			break;
		case 0:		//0.退出通讯录
			cout << "欢迎下次使用" << endl;
			return 0;
			break;
		default:
			break;	
		}
	}
	return 0;
}
