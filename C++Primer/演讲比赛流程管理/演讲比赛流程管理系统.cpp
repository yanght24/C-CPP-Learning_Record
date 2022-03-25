#include<iostream>
#include<ctime>
#include "speechManager.h"
using namespace std;

int main()
{
	//随机数种子
	srand((unsigned int)time(NULL)); 
	
	//创建管理类的对象
	SpeechManager sm;
	
	int choice = 0;		//存储用户选项
	
	while(true)
	{
		sm.show_Menu();
		
		cout << "请输入你的选择: " << endl;
		cin >> choice;
		
		switch(choice)
		{
		case 1:			//开始比赛
			sm.startSpeech();
			break;
		case 2:			//查看往届记录
			sm.showRecord();
			break;
		case 3:			//清空比赛记录 
			sm.clearRecord();
			break;
		case 0:			//退出系统
			sm.exit_System();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	
	system("pause");
	return 0;
}
