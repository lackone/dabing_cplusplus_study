#include <iostream>

using namespace std;

struct MyException
{
	MyException(const string& msg) : _msg(msg)
	{

	}
	string _msg;
};

//函数后添加了throw异常接口声明，其参数表示可以抛出的异常类型，分别为int 和MyException 类型
double division(int a, int b) throw(MyException, int)
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

//divisionMethod 没有添加异常接口声明，表示在该函数中可以抛出任意类型的异常
double division2(int a, int b)
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

// 函数后添加了throw异常接口声明，其参数列表为空，表示该函数不允许抛出异常。
double division3(int a, int b) throw()
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

//表示函数不会抛出异常的动态异常声明 throw() 也被新的 noexcept 异常声明所取代

//简单地在函数声明后加上 noexcept 关键字

//可以接受一个常量表达式作为参数，如下所示∶
//double divisionMethod(int a, int b) noexcept(常量表达式);
//常量表达式的结果会被转换成一个bool类型的值：
//值为 true，表示函数不会抛出异常
//值为 false，表示有可能抛出异常这里
//不带常量表达式的noexcept相当于声明了noexcept（true），即不会抛出异常。

double division4(int a, int b) noexcept
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

int main()
{
	try
	{
		throw - 1;
	}
	catch (int e)
	{
		cout << e << endl;

	}

	try
	{
		double ret = division(2, 0);
		cout << ret << endl;
	}
	catch (const MyException& e)
	{
		cout << e._msg << endl;
	}
	catch (int e)
	{
		cout << e << endl;
	}

	//cout << division3(2, 0) << endl;

	cout << division4(2, 0) << endl;

	return 0;
}