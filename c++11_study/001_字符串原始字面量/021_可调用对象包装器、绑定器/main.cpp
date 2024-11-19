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

//在C++中存在“可调用对象”这么一个概念。准确来说，可调用对象有如下几种定义：
//1、是一个函数指针
//2、是一个具有operator()成员函数的类对象（仿函数）
//3、是一个可被转换为函数指针的类对象
//4、是一个类成员函数指针或者类成员指针
int main()
{
	//函数指针
	pFunc p = &print;
	p(22);

	//可调用对象
	Test t;
	t("test");

	Test2 t2;
	t2(33);

	void (Test3:: * func_ptr)(int) = &Test3::print;
	int Test3::* p_num = &Test3::m_i;

	Test3 t3;
	(t3.*func_ptr)(44);
	t3.*p_num = 1;

	//C++11通过提供std::function 和 std::bind统一了可调用对象的各种操作。

	//std::function<返回值类型(参数类型列表)> diy_name = 可调用对象;

	function<int(int, int)> f1 = add;
	function<int(int, int)> f2 = T1::sub;
	T2 tt2;
	function<int(int, int)> f3 = tt2;

	cout << f1(3, 3) << endl;
	cout << f2(3, 3) << endl;
	cout << f3(3, 3) << endl;

	//std::bind用来将可调用对象与其参数一起进行绑定。绑定后的结果可以使用std::function进行保存，并延迟调用到任何我们需要的时候。
	//将可调用对象与其参数一起绑定成一个仿函数。
	//将多元（参数个数为n，n > 1）可调用对象转换为一元或者（n - 1）元可调用对象，即只绑定部分参数。

	// 绑定非类成员函数/变量
	//auto f = std::bind(可调用对象地址, 绑定的参数 / 占位符);
	// 绑定类成员函/变量
	//auto f = std::bind(类函数 / 成员地址, 类实例对象地址, 绑定的参数 / 占位符);

	auto fb = bind(output, placeholders::_1);
	for (int i = 0; i < 10; i++)
	{
		callFunc(i, fb);
	}

	return 0;
}