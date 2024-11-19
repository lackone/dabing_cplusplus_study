#include <iostream>

using namespace std;

struct Test
{
	int id;
	int num;
};

//1、函数必须要有返回值，并且return 返回的表达式必须是常量表达式。
//2、函数在使用之前，必须有对应的定义语句。
//3、整个函数的函数体中，不能出现非常量表达式之外的语句（using 指令、typedef 语句以及 static_assert 断言、return语句除外）。

// error，不是常量表达式函数
constexpr void func1()
{
	int a = 100;
	cout << "a: " << a << endl;
}

// error，不是常量表达式函数
constexpr int func1()
{
	int a = 100;
	return a;
}

class A
{
public:
	//类成员函数
	constexpr int func()
	{
		constexpr int v = 100;
		return 5 * v;
	}
};

struct Person
{
	const char* name;
	int age;
};

//修饰模板函数
template<typename T>
constexpr T display(T t)
{
	return t;
}

struct Person2
{
	//构造函数的函数体必须为空，并且必须采用初始化列表的方式为各个成员赋值。
	constexpr Person2(const char* p, int age) :name(p), age(age)
	{

	}
	const char* name;
	int age;
};

int main()
{
	//const关键字，从功能上来说这个关键字有双重语义：变量只读，修饰常量
	const int cnt = 10;
	int arr[cnt]; // ok，cnt 是一个常量

	//C++11中添加了一个新的关键字constexpr，这个关键字是用来修饰常量表达式的。
	//所谓常量表达式，指的就是由多个（≥1）常量（值不会改变）组成并且在编译过程中就得到计算结果的表达式。

	constexpr int i = 100;
	constexpr int j = i + 200;

	constexpr Test t{ 1, 2 };

	//t.num += 100; //对象t是一个常量，因此它的成员也是常量

	A a;
	constexpr int v = a.func();

	struct Person p { "test", 22 };
	struct Person p2 = display(p); //普通函数

	constexpr int ret = display(200); //常量表达式函数

	constexpr struct Person p3 = { "test", 33 };
	constexpr struct Person p4 = display(p3); //常量表达式函数

	return 0;
}