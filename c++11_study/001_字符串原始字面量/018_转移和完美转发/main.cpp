#include <iostream>

using namespace std;

class Test
{
public:
	Test()
	{

	}
};

template<typename T>
void printValue(T& t)
{
	cout << "lvalue" << t << endl;
}

template<typename T>
void printValue(T&& t)
{
	cout << "rvalue" << t << endl;
}

//当T为左值引用类型时，t将被转换为T类型的左值
//当T不是左值引用类型时，t将被转换为T类型的右值
template<typename T>
void testForward(T&& v)
{
	printValue(v);
	printValue(move(v));
	printValue(forward<T>(v));
	cout << endl;
}

int main()
{
	//使用std::move方法可以将左值转换为右值。使用这个函数并不能移动任何东西，而是和移动构造函数一样都具有移动语义，将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存拷贝。

	Test t;
	//Test&& t1 = t; //t是左值
	Test&& t2 = move(t); //使用move()函数将左值转换为了右值，这样就可以初始化右值引用了。

	testForward(520);
	int num = 1314;
	testForward(num);
	testForward(forward<int>(num));
	testForward(forward<int&>(num));
	testForward(forward<int&&>(num));

	return 0;
}