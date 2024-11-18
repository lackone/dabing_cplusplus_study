#include <iostream>

using namespace std;

class A
{
public:
	virtual void test()
	{
		cout << "aaa" << endl;
	}
};

class B : public A
{
public:
	void test() override //检查父类的虚函数
	{
		cout << "bbb" << endl;
	}
};

class C : public B
{
public:
	void test() override
	{
		cout << "ccc" << endl;
	}
};

//override关键字确保在派生类中声明的重写函数与基类的虚函数有相同的签名，同时也明确表明将会重写基类的虚函数，这样就可以保证重写的虚函数的正确性，
//也提高了代码的可读性，和final一样这个关键字要写到方法的后面。
int main()
{

	return 0;
}
