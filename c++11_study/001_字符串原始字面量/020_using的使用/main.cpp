#include <iostream>

using namespace std;

//在C++中using用于声明命名空间，使用命名空间也可以防止命名冲突。

//1. 定义别名
//typedef 旧的类型名 新的类型名;
typedef unsigned int uint_t;

//using 新的类型 = 旧的类型;
using uint_t = int;

//2. 模板的别名

template <typename T>
// 定义外敷类
struct MyMap
{
	typedef map<int, T> type;
};

template <typename T>
using mymap = map<int, T>;

void test()
{
	cout << "test" << endl;
}

using test2 = void(*)();

//using语法和typedef一样，并不会创建出新的类型，它们只是给某些类型定义了新的别名。
// using相较于typedef的优势在于定义函数指针别名时看起来更加直观，并且可以给模板定义别名。
int main()
{
	test2 t;
	t = test;
	t();

	return 0;
}