#include <iostream>

using namespace std;

class A
{
public:
	virtual void test()
	{
		cout << "aaa" << endl;
	}
};

class B : public A
{
public:
	void test() override //��鸸����麯��
	{
		cout << "bbb" << endl;
	}
};

class C : public B
{
public:
	void test() override
	{
		cout << "ccc" << endl;
	}
};

//override�ؼ���ȷ��������������������д�����������麯������ͬ��ǩ����ͬʱҲ��ȷ����������д������麯���������Ϳ��Ա�֤��д���麯������ȷ�ԣ�
//Ҳ����˴���Ŀɶ��ԣ���finalһ������ؼ���Ҫд�������ĺ��档
int main()
{

	return 0;
}
