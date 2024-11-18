#include <iostream>

using namespace std;

template<typename T = int, T t = 100>
class Test
{
public:
	void print()
	{
		cout << t << endl;
	}
};

//C++11中添加了对函数模板默认参数的支持
template<typename T = int>
void func(T t)
{
	cout << t << endl;
}

//如果可以推导出参数类型则使用推导出的类型
//如果函数模板无法推导出参数类型，那么编译器会使用默认模板参数
//如果无法推导出模板参数类型并且没有设置默认模板参数，编译器就会报错。
template<typename T = int, typename N>
T func2(N arg)
{
	return arg;
}

template<typename T, typename U = char>
void func3(T arg1 = 100, U arg2 = 100)
{
	cout << arg1 << " " << arg2 << endl;
}

int main()
{
	//当所有模板参数都有默认参数时，函数模板的调用如同一个普通函数。但对于类模板而言，哪怕所有参数都有默认参数，在使用时也必须在模板名后跟随<>来实例化。
	Test<> test;
	test.print();

	func(100);

	cout << func2(3.14) << endl;

	cout << func2(111) << endl;

	func3('a'); //推导T=char,默认U=char
	func3(97, 'a'); //推导T=int,推导U=char
	//func(); //无法推导，也没有默认

	return 0;
}