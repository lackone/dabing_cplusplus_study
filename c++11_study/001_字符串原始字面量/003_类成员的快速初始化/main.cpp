#include <iostream>

using namespace std;

struct Base
{
	Base() : a(222) {}

	int a;
	int b = 1;
	double cc = 3.33;
	char ch = 'a';
	//类的静态成员，必须在类的外部进行初始化
	static int c;
	static const double d;
	static const char* const e;
	//静态常量，类型是整形或者枚举
	const static int f = 0;
};

int Base::c = 8;
const double Base::d = 4.44;
const char* const Base::e = "hello";

// C++11 中在类内部有两种初始化方式 = {}

struct Test
{
	Test() : a(222)
	{
	}

	int a{ 4 };
	string str1{ "test" };
	string str2 = "test";
	//string str3("test"); //错误的
};

int main()
{

	Test t;
	//通过初始化列表指定的值会覆盖就地初始化时指定的值。
	cout << t.a << endl;

	return 0;
}