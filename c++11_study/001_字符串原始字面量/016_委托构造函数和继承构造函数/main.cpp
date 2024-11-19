#include <iostream>

using namespace std;

//委托构造函数允许使用同一个类中的一个构造函数调用其它的构造函数，从而简化相关变量的初始化。
class Test
{
public:
	Test()
	{

	}
	Test(int max)
	{
		m_max = max;
	}
	//这种链式的构造函数调用不能形成一个闭环（死循环），否则会在运行期抛异常。
	//如果要进行多层构造函数的链式调用，建议将构造函数的调用的写在初始列表中而不是函数体内部，否则编译器会提示形参的重复定义。
	//在初始化列表中调用了代理构造函数初始化某个类成员变量之后，就不能在初始化列表中再次初始化这个变量了。
	Test(int min, int max) : Test(max)
	{
		//Test(max); //此处编译器会报错, 提示形参max被重复定义
		m_min = min;
	}
	//错误, 使用了委托构造函数就不能再次m_max初始化了
	//Test(int min, int max) : Test(max), m_max(max)
	//{
	//
	//}
	Test(int min, int max, int mid) : Test(min, max)
	{
		m_mid = mid;
	}
public:
	int m_min;
	int m_max;
	int m_mid;
};

class Base
{
public:
	Base(int i) :m_i(i) {}
	Base(int i, double j) :m_i(i), m_d(j) {}
	Base(int i, double j, string k) :m_i(i), m_d(j), m_str(k) {}
	void func(int i)
	{
		cout << "base func" << i << endl;
	}
	int m_i;
	double m_d;
	string m_str;
};

class Child : public Base
{
public:
	//在子类中初始化从基类继承的类成员，需要在子类中重新定义和基类一致的构造函数，这是非常繁琐的
	Child(int i) :Base(i) {}
	Child(int i, double j) :Base(i, j) {}
	Child(int i, double j, string k) :Base(i, j, k) {}
};

class Child2 : public Base
{
public:
	using Base::Base; //通过使用using 类名::构造函数名（其实类名和构造函数名是一样的）来声明使用基类的构造函数

	//子类中的func()函数隐藏了基类中的两个func()因此默认情况下通过子类对象只能调用无参的func()，
	//在上面的子类代码中添加了using Base::func;之后，就可以通过子类对象直接调用父类中被隐藏的带参func()函数了。
	using Base::func; 

	void func()
	{
		cout << "child2" << endl;
	}
};

int main()
{
	Test t(10, 20, 30);
	cout << t.m_min << t.m_max << t.m_mid << endl;

	Child2 ch(1, 3.4, "test");
	cout << ch.m_i << ch.m_d << ch.m_str << endl;

	ch.func();
	ch.Base::func(11);
	ch.func(22);

	return 0;
}