#include <iostream>
#include <cassert>

using namespace std;

//使用了断言assert(expression) ，这是一个宏，它的参数是一个表达式，这个表达式通常返回一个布尔类型的值，并且要求表达式必须为 true 程序才能继续向下执行，否则会直接中断。
char* newChar(size_t size)
{
	//assert是一个运行时断言，也就是说它只有在程序运行时才能起作用
	assert(size > 0);
	char* p = new char[size];
	return p;
}

int main()
{
	//静态断言static_assert，所谓静态就是在编译时就能够进行检查的断
	static_assert(sizeof(void*) == 4, "不是32位");
	static_assert(sizeof(void*) == 8, "不是64位");

	cout << sizeof(int) << endl;
	cout << sizeof(long) << endl;


	char* p = newChar(0);

	strcpy_s(p, 16, "test");

	cout << p << endl;

	delete[] p;

	return 0;
}