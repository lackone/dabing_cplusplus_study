#include <iostream>

using namespace std;

struct Base
{
	Base() : a(222) {}

	int a;
	int b = 1;
	double cc = 3.33;
	char ch = 'a';
	//��ľ�̬��Ա������������ⲿ���г�ʼ��
	static int c;
	static const double d;
	static const char* const e;
	//��̬���������������λ���ö��
	const static int f = 0;
};

int Base::c = 8;
const double Base::d = 4.44;
const char* const Base::e = "hello";

// C++11 �������ڲ������ֳ�ʼ����ʽ = {}

struct Test
{
	Test() : a(222)
	{
	}

	int a{ 4 };
	string str1{ "test" };
	string str2 = "test";
	//string str3("test"); //�����
};

int main()
{

	Test t;
	//ͨ����ʼ���б�ָ����ֵ�Ḳ�Ǿ͵س�ʼ��ʱָ����ֵ��
	cout << t.a << endl;

	return 0;
}