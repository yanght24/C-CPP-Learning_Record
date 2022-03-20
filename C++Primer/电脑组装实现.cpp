#include<iostream>
using namespace std;

//抽象不同的零件类;
class CPU
{
public:
	//抽象的计算函数
	virtual void calculate() = 0;
};

class VideoCard
{
public:
	//抽象的显示函数
	virtual void display() = 0;
};

class Memory
{
public:
	//抽象的存储函数
	virtual void storage() = 0;
};

//电脑类;
class Computer
{
public:
	Computer(CPU *cpu, VideoCard *vc, Memory *mem)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}
	~Computer()
	{
		if(m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
		}
		if(m_vc != NULL)
		{
			delete m_vc;
			m_vc = NULL;
		}
		if(m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}
	
	//工作函数
	void work()
	{
		m_cpu->calculate();
		m_vc->display();
		m_mem->storage();
	}
	
private:
	
	CPU *m_cpu;		//CPU零件指针
	VideoCard *m_vc;	//显卡零件指针
	Memory *m_mem;	//内存条零件指针
};

//具体厂商;
class IntelCPU : public CPU
{
public:
	virtual void calculate()
	{
		cout << "Intel的CPU开始计算" << endl;
	}
};
class IntelVideoCard : public VideoCard
{
public:
	virtual void display()
	{
		cout << "Intel的显卡开始显示" << endl;
	}
};
class IntelMemory : public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel的内存条开始存储" << endl;
	}
};

class AMDCPU : public CPU
{
public:
	virtual void calculate()
	{
		cout << "AMD的CPU开始计算" << endl;
	}
};
class AMDVideoCard : public VideoCard
{
public:
	virtual void display()
	{
		cout << "AMD的显卡开始显示" << endl;
	}
};
class AMDMemory : public Memory
{
public:
	virtual void storage()
	{
		cout << "AMD的内存条开始存储" << endl;
	}
};

void test01()
{
	//第一台电脑零件
	CPU *intelCPU = new IntelCPU;
	VideoCard *intelCard = new IntelVideoCard;
	Memory *intelMem = new IntelMemory;
	//第一台电脑
	cout << "第一台电脑开始工作" << endl;
	Computer *computer1 = new Computer(intelCPU, intelCard, intelMem);
	computer1->work();
	delete computer1;
	
	cout << "*************************" << endl;
	
	//第二台电脑
	cout << "第二台电脑开始工作" << endl;
	Computer *computer2 = new Computer(new AMDCPU, new AMDVideoCard, new AMDMemory);
	computer2->work();
	delete computer2;
	
	cout << "*************************" << endl;
	
	//第三台电脑
	cout << "第三台电脑开始工作" << endl;
	Computer *computer3 = new Computer(new IntelCPU, new AMDVideoCard, new AMDMemory);
	computer3->work();
	delete computer3;
}

int main()
{
	test01();
	
	return 0;
}
