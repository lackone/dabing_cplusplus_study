#include <iostream>
#include <map>

using namespace std;

//不能作为函数参数使用
void func(auto a, auto b)
{
	cout << a << " " << b << endl;
}

//不能用于类的非静态成员变量的初始化
class Test
{
	auto v1 = 0; //错误
	static auto v2 = 0; //错误
	static const auto v3 = 0;
};

//不能使用auto关键字定义数组
void func3()
{
	int arr[] = { 1, 2, 3 };
	auto a1 = arr; // auto = int*
	auto a2[] = arr; //错误
	auto a3[] = { 1, 2, 3 }; //错误
}

template<typename T>
struct Test {};

//无法使用auto推导出模板参数
void func4()
{
	Test<double> t;
	Test<auto> t1 = t; //错误
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
	decltype(T().begin()) m_it; // 这里不能确定迭代器类型
};

//在C++11中增加了返回类型后置语法，说明白一点就是将decltype和auto结合起来完成返回类型的推导
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

//decltype结合返回值后置语法很容易推导出来 test(t)函数可能出现的返回值类型，并将其作用到了函数myFunc()上。
template<typename T>
auto myFunc(T& t) -> decltype(test(t))
{
	return test(t);
}

//使用auto声明的变量必须要进行初始化，以让编译器推导出它的实际类型，在编译时将auto占位符替换为真正的类型。
int main()
{
	//必须初始化才能推导
	auto x = 3;
	auto y = "test";

	//当变量不是指针或者引用类型时，推导的结果中不会保留const、volatile关键字
	//当变量是指针或者引用类型时，推导的结果中会保留const、volatile关键字
	int tmp = 222;
	const auto a1 = tmp; // auto = int
	auto a2 = a1; // auto = int
	const auto& a3 = tmp; //auto = int
	auto& a4 = a3; //auto = const int

	//auto 的用处
	//1、用于容器的遍历
	map<int, string> m;
	for (auto it = m.begin(); it != m.end(); it++)
	{

	}

	//decltype
	//它的作用是在编译器编译的时候推导出一个表达式的类型
	//decltype推导的表达式可简单可复杂，auto只能推导已初始化的变量类型
	int a = 11;
	decltype(a) b = 99;
	decltype(a + 3.14) c = 2.32;
	decltype(a + b * c) d = 2.523;

	//表达式为普通变量或者普通表达式或者类表达式，在这种情况下，使用decltype推导出的类型和表达式的类型是一致的。
	//表达式是函数调用，使用decltype推导出的类型和函数返回值一致。
	//表达式是一个左值，或者被括号( )包围，使用 decltype推导出的是表达式类型的引用（如果有const、volatile限定符不能忽略）。

	return 0;
}