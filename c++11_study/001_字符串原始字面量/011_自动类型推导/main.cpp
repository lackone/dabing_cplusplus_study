#include <iostream>
#include <map>

using namespace std;

//������Ϊ��������ʹ��
void func(auto a, auto b)
{
	cout << a << " " << b << endl;
}

//����������ķǾ�̬��Ա�����ĳ�ʼ��
class Test
{
	auto v1 = 0; //����
	static auto v2 = 0; //����
	static const auto v3 = 0;
};

//����ʹ��auto�ؼ��ֶ�������
void func3()
{
	int arr[] = { 1, 2, 3 };
	auto a1 = arr; // auto = int*
	auto a2[] = arr; //����
	auto a3[] = { 1, 2, 3 }; //����
}

template<typename T>
struct Test {};

//�޷�ʹ��auto�Ƶ���ģ�����
void func4()
{
	Test<double> t;
	Test<auto> t1 = t; //����
}

template<typename T>
class Container
{
public:
	void func(T& c)
	{
		for (m_it = c.begin(); m_it != c.end(); ++m_it)
		{
			cout << *m_it << endl;
		}
	}
private:
	decltype(T().begin()) m_it; // ���ﲻ��ȷ������������
};

//��C++11�������˷������ͺ����﷨��˵����һ����ǽ�decltype��auto���������ɷ������͵��Ƶ�
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u)
{
	return t + u;
}

int& test(int& i)
{
	return i;
}

double& test(double& d)
{
	return d;
}

//decltype��Ϸ���ֵ�����﷨�������Ƶ����� test(t)�������ܳ��ֵķ���ֵ���ͣ����������õ��˺���myFunc()�ϡ�
template<typename T>
auto myFunc(T& t) -> decltype(test(t))
{
	return test(t);
}

//ʹ��auto�����ı�������Ҫ���г�ʼ�������ñ������Ƶ�������ʵ�����ͣ��ڱ���ʱ��autoռλ���滻Ϊ���������͡�
int main()
{
	//�����ʼ�������Ƶ�
	auto x = 3;
	auto y = "test";

	//����������ָ�������������ʱ���Ƶ��Ľ���в��ᱣ��const��volatile�ؼ���
	//��������ָ�������������ʱ���Ƶ��Ľ���лᱣ��const��volatile�ؼ���
	int tmp = 222;
	const auto a1 = tmp; // auto = int
	auto a2 = a1; // auto = int
	const auto& a3 = tmp; //auto = int
	auto& a4 = a3; //auto = const int

	//auto ���ô�
	//1�����������ı���
	map<int, string> m;
	for (auto it = m.begin(); it != m.end(); it++)
	{

	}

	//decltype
	//�����������ڱ����������ʱ���Ƶ���һ�����ʽ������
	//decltype�Ƶ��ı��ʽ�ɼ򵥿ɸ��ӣ�autoֻ���Ƶ��ѳ�ʼ���ı�������
	int a = 11;
	decltype(a) b = 99;
	decltype(a + 3.14) c = 2.32;
	decltype(a + b * c) d = 2.523;

	//���ʽΪ��ͨ����������ͨ���ʽ��������ʽ������������£�ʹ��decltype�Ƶ��������ͺͱ��ʽ��������һ�µġ�
	//���ʽ�Ǻ������ã�ʹ��decltype�Ƶ��������ͺͺ�������ֵһ�¡�
	//���ʽ��һ����ֵ�����߱�����( )��Χ��ʹ�� decltype�Ƶ������Ǳ��ʽ���͵����ã������const��volatile�޶������ܺ��ԣ���

	return 0;
}