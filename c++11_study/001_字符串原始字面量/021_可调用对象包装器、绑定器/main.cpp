#include <iostream>
#include <functional>

using namespace std;

int print(int a)
{
	cout << a << endl;
	return a;
}

typedef int (*pFunc)(int);
using pFunc = int(*)(int);

struct Test
{
	void operator()(string msg)
	{
		cout << msg << endl;
	}
};

struct Test2
{
	operator pFunc()
	{
		return print;
	}
};

struct Test3
{
	void print(int a)
	{
		cout << a << endl;
	}
	int m_i;
};

int add(int a, int b)
{
	return a + b;
}

class T1
{
public:
	static int sub(int a, int b)
	{
		return a - b;
	}
};

class T2
{
public:
	int operator()(int a, int b)
	{
		return a * b;
	}
};

void callFunc(int x, const function<void(int)>& func)
{
	if (x % 2 == 0)
	{
		func(x);
	}
}

void output(int x)
{
	cout << x << endl;
}

//��C++�д��ڡ��ɵ��ö�����ôһ�����׼ȷ��˵���ɵ��ö��������¼��ֶ��壺
//1����һ������ָ��
//2����һ������operator()��Ա����������󣨷º�����
//3����һ���ɱ�ת��Ϊ����ָ��������
//4����һ�����Ա����ָ��������Աָ��
int main()
{
	//����ָ��
	pFunc p = &print;
	p(22);

	//�ɵ��ö���
	Test t;
	t("test");

	Test2 t2;
	t2(33);

	void (Test3:: * func_ptr)(int) = &Test3::print;
	int Test3::* p_num = &Test3::m_i;

	Test3 t3;
	(t3.*func_ptr)(44);
	t3.*p_num = 1;

	//C++11ͨ���ṩstd::function �� std::bindͳһ�˿ɵ��ö���ĸ��ֲ�����

	//std::function<����ֵ����(���������б�)> diy_name = �ɵ��ö���;

	function<int(int, int)> f1 = add;
	function<int(int, int)> f2 = T1::sub;
	T2 tt2;
	function<int(int, int)> f3 = tt2;

	cout << f1(3, 3) << endl;
	cout << f2(3, 3) << endl;
	cout << f3(3, 3) << endl;

	//std::bind�������ɵ��ö����������һ����а󶨡��󶨺�Ľ������ʹ��std::function���б��棬���ӳٵ��õ��κ�������Ҫ��ʱ��
	//���ɵ��ö����������һ��󶨳�һ���º�����
	//����Ԫ����������Ϊn��n > 1���ɵ��ö���ת��ΪһԪ���ߣ�n - 1��Ԫ�ɵ��ö��󣬼�ֻ�󶨲��ֲ�����

	// �󶨷����Ա����/����
	//auto f = std::bind(�ɵ��ö����ַ, �󶨵Ĳ��� / ռλ��);
	// �����Ա��/����
	//auto f = std::bind(�ຯ�� / ��Ա��ַ, ��ʵ�������ַ, �󶨵Ĳ��� / ռλ��);

	auto fb = bind(output, placeholders::_1);
	for (int i = 0; i < 10; i++)
	{
		callFunc(i, fb);
	}

	return 0;
}