#include <iostream>

using namespace std;

void func(char* p)
{
	cout << "func(char* p)" << endl;
}

void func(int p)
{
	cout << "func(int p)" << endl;
}

int main()
{
	//C++98/03 标准中，将一个指针初始化为空指针的方式有 2 种：

	char* p = 0;
	char* p2 = NULL;

	//在C++中NULL和0是等价的
	//调用的都是 void func(int p)
	func(NULL);
	func(222);

	//C++11 标准并没有对 NULL 的宏定义做任何修改，而是另其炉灶，引入了一个新的关键字nullptr
	int* p3 = nullptr;
	char* p4 = nullptr;
	double* p5 = nullptr;

	//nullptr 无法隐式转换为整形，但是可以隐式匹配指针类型。在 C++11 标准下，相比 NULL 和 0，使用 nullptr 初始化空指针可以令我们编写的程序更加健壮
	func(nullptr); //调用func(char* p)
	func(333);

	return 0;
}
