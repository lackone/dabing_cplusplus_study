#include <iostream>

using namespace std;

class A
{
public:
	virtual void test() //�����ڻ����麯�������final
	{
		cout << "aaa" << endl;
	}
};

class B : public A
{
public:
	//���ʹ��final���κ�����ֻ�������麯��������������ֹ������д�������������ˣ�
	void test() final
	{
		cout << "bbb" << endl;
	}
};

class C : public B
{
public:
	// �﷨����, ��������д
	void test()
	{
		cout << "ccc" << endl;
	}
};

class Base final
{

};

//ʹ��final�ؼ������ι������ǲ������̳еģ�Ҳ����˵����಻���������ࡣ
class Child : public Base
{

};

//C++��������final�ؼ���������ĳ���಻�ܱ��̳У�����ĳ���麯�����ܱ���д
int main()
{

	return 0;
}
