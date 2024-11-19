#include <iostream>

using namespace std;

//C++11 增加了一个新的类型，称为右值引用（ R-value reference），标记为 &&

//lvalue 是loactor value的缩写，rvalue 是 read value的缩写
//左值是指存储在内存中、有明确存储地址（可取地址）的数据；
//右值是指可以提供数据值的数据（不可取地址）；

//无论声明左值引用还是右值引用都必须立即进行初始化，因为引用类型本身并不拥有所绑定对象的内存，只是该对象的一个别名。
//通过右值引用的声明，该右值又“重获新生”，其生命周期与右值引用类型变量的生命周期一样，只要该变量还活着，该右值临时量将会一直存活下去。

class Test
{
public:
	Test() : m_i(new int(111))
	{
		cout << "构造" << endl;
	}

	//拷贝构造
	Test(const Test& copy) : m_i(new int(*copy.m_i))
	{
		cout << "copy" << endl;
	}

	//右值引用具有移动语义，移动语义可以将资源（堆、系统对象等）通过浅拷贝从一个对象转移到另一个对象这样就能减少不必要的临时对象的创建、拷贝以及销毁，可以大幅提高C++应用程序的性能。
	//移动构造
	Test(Test&& copy) noexcept : m_i(copy.m_i)
	{
		cout << "move" << endl;
		copy.m_i = nullptr;
	}

	~Test()
	{
		cout << "析构" << endl;
		delete m_i;
	}

	int* m_i;
};

Test getTest()
{
	Test t;
	return t;
}

int main()
{
	//移动构造中使用了右值引用，会将临时对象中的堆内存地址的所有权转移给对象t，这块内存被成功续命，因此在t对象中还可以继续使用这块内存。
	Test t = getTest();
	cout << *t.m_i << endl;

	int x = 520, y = 1314;
	auto&& v1 = x;
	auto&& v2 = 250;
	//decltype(x) && v3 = y;   // error
	cout << "v1: " << v1 << ", v2: " << v2 << endl;

	//通过右值推导 T&& 或者 auto&& 得到的是一个右值引用类型
	//通过非右值（右值引用、左值、左值引用、常量右值引用、常量左值引用）推导 T&& 或者 auto&& 得到的是一个左值引用类型

	//左值和右值是独立于他们的类型的，右值引用类型可能是左值也可能是右值。
	//编译器会将已命名的右值引用视为左值，将未命名的右值引用视为右值。
	//auto&& 或者函数参数类型自动推导的T&& 是一个未定的引用类型，它可能是左值引用也可能是右值引用类型，这取决于初始化的值类型（上面有例子）。
	//通过右值推导 T&& 或者 auto&& 得到的是一个右值引用类型，其余都是左值引用类型。

	return 0;
}