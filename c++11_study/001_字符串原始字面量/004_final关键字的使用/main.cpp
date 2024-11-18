#include <iostream>

using namespace std;

class A
{
public:
	virtual void test() //不会在基类虚函数中添加final
	{
		cout << "aaa" << endl;
	}
};

class B : public A
{
public:
	//如果使用final修饰函数，只能修饰虚函数，这样就能阻止子类重写父类的这个函数了：
	void test() final
	{
		cout << "bbb" << endl;
	}
};

class C : public B
{
public:
	// 语法错误, 不允许重写
	void test()
	{
		cout << "ccc" << endl;
	}
};

class Base final
{

};

//使用final关键字修饰过的类是不允许被继承的，也就是说这个类不能有派生类。
class Child : public Base
{

};

//C++中增加了final关键字来限制某个类不能被继承，或者某个虚函数不能被重写
int main()
{

	return 0;
}
