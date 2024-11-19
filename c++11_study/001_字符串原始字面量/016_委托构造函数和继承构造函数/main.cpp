#include <iostream>

using namespace std;

//ί�й��캯������ʹ��ͬһ�����е�һ�����캯�����������Ĺ��캯�����Ӷ�����ر����ĳ�ʼ����
class Test
{
public:
	Test()
	{

	}
	Test(int max)
	{
		m_max = max;
	}
	//������ʽ�Ĺ��캯�����ò����γ�һ���ջ�����ѭ����������������������쳣��
	//���Ҫ���ж�㹹�캯������ʽ���ã����齫���캯���ĵ��õ�д�ڳ�ʼ�б��ж����Ǻ������ڲ����������������ʾ�βε��ظ����塣
	//�ڳ�ʼ���б��е����˴����캯����ʼ��ĳ�����Ա����֮�󣬾Ͳ����ڳ�ʼ���б����ٴγ�ʼ����������ˡ�
	Test(int min, int max) : Test(max)
	{
		//Test(max); //�˴��������ᱨ��, ��ʾ�β�max���ظ�����
		m_min = min;
	}
	//����, ʹ����ί�й��캯���Ͳ����ٴ�m_max��ʼ����
	//Test(int min, int max) : Test(max), m_max(max)
	//{
	//
	//}
	Test(int min, int max, int mid) : Test(min, max)
	{
		m_mid = mid;
	}
public:
	int m_min;
	int m_max;
	int m_mid;
};

class Base
{
public:
	Base(int i) :m_i(i) {}
	Base(int i, double j) :m_i(i), m_d(j) {}
	Base(int i, double j, string k) :m_i(i), m_d(j), m_str(k) {}
	void func(int i)
	{
		cout << "base func" << i << endl;
	}
	int m_i;
	double m_d;
	string m_str;
};

class Child : public Base
{
public:
	//�������г�ʼ���ӻ���̳е����Ա����Ҫ�����������¶���ͻ���һ�µĹ��캯�������Ƿǳ�������
	Child(int i) :Base(i) {}
	Child(int i, double j) :Base(i, j) {}
	Child(int i, double j, string k) :Base(i, j, k) {}
};

class Child2 : public Base
{
public:
	using Base::Base; //ͨ��ʹ��using ����::���캯��������ʵ�����͹��캯������һ���ģ�������ʹ�û���Ĺ��캯��

	//�����е�func()���������˻����е�����func()���Ĭ�������ͨ���������ֻ�ܵ����޲ε�func()��
	//���������������������using Base::func;֮�󣬾Ϳ���ͨ���������ֱ�ӵ��ø����б����صĴ���func()�����ˡ�
	using Base::func; 

	void func()
	{
		cout << "child2" << endl;
	}
};

int main()
{
	Test t(10, 20, 30);
	cout << t.m_min << t.m_max << t.m_mid << endl;

	Child2 ch(1, 3.4, "test");
	cout << ch.m_i << ch.m_d << ch.m_str << endl;

	ch.func();
	ch.Base::func(11);
	ch.func(22);

	return 0;
}