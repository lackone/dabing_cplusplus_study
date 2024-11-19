#include <iostream>

using namespace std;

//在C++中声明自定义的类，编译器会默认帮助程序员生成一些他们未自定义的成员函数。
//无参构造函数：创建类对象
//拷贝构造函数：拷贝类对象
//移动构造函数：拷贝类对象
//拷贝赋值函数：类对象赋值
//移动赋值函数：类对象赋值
//析构函数：销毁类对象
//在C++语法规则中，一旦程序员实现了这些函数的自定义版本，则编译器不会再为该类自动生成默认版本。

//在C++11标准中称= default修饰的函数为显式默认【缺省】（explicit defaulted）函数，而称=delete修饰的函数为删除（deleted）函数或者显示删除函数。

class Base
{
public:
	Base() = default;
	Base(const Base& obj) = default;
	Base(Base&& obj) = default;
	Base& operator= (const Base& obj) = default;
	Base& operator= (Base&& obj) = default;
	~Base() = default;

	// 以下写法全部都是错误的
	Base(int a = 0) = default;
	Base(int a, int b) = default;
	void print() = default;
	bool operator== (const Base& obj) = default;
	bool operator>=(const Base& obj) = default;
};

class Base2
{
public:
	Base2() = default;
	//=delete 表示显示删除，`显式删除可以避免用户使用一些不应该使用的类的成员函数`，使用这种方式可以有效的防止某些类型之间自动进行隐式类型转换产生的错误。
	Base2(const Base2& obj) = delete;
	Base2& operator= (const Base2& obj) = delete;
	//禁止使用自定义函数
	void print(char c) = delete;
};

int main()
{
	Base2 b;
	//Base2 tmp1(b);    // error
	//Base2 tmp = b;    // error

	return 0;
}