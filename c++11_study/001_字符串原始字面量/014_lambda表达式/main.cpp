#include <iostream>
#include <functional>

using namespace std;

//声明式的编程风格：就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或函数对象。
//简洁：避免了代码膨胀和功能分散，让开发更加高效。
//在需要的时间和地点实现功能闭包，使程序更加灵活。

// [capture](params) opt -> ret {body;};
// 其中capture是捕获列表，params是参数列表，opt是函数选项，ret是返回值类型，body是函数体。

/*
[] - 不捕捉任何变量
[&] - 捕获外部作用域中所有变量, 并作为引用在函数体内使用 (按引用捕获)
[=] - 捕获外部作用域中所有变量, 并作为副本在函数体内使用 (按值捕获)
			拷贝的副本在匿名函数体内部是只读的
[=, &foo] - 按值捕获外部作用域中所有变量, 并按照引用捕获外部变量 foo
[bar] - 按值捕获 bar 变量, 同时不捕获其他变量
[&bar] - 按引用捕获 bar 变量, 同时不捕获其他变量
[this] - 捕获当前类中的this指针
			让lambda表达式拥有和当前类成员函数同样的访问权限
			如果已经使用了 & 或者 =, 默认添加此选项
*/

int main()
{
	auto f = [](int a)
		{
			return a + 10;
		};

	int a = 11;

	//被mutable修改是lambda表达式就算没有参数也要写明参数列表，并且可以去掉按值捕获的外部变量的只读（const）属性。
	auto f1 = [=]() mutable
		{
			return ++a;
		};

	//lambda表达式的类型在C++11中会被看做是一个带operator()的类，即仿函数。
	//按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。

	cout << f1() << endl;
	cout << a << endl;

	//可以使用std::function和std::bind来存储和操作lambda表达式
	function<int(int)> f3 = [](int a) {return a; };
	function<int(int)> f4 = bind([](int a) {return a;  }, placeholders::_1);

	cout << f3(111) << endl;
	cout << f4(222) << endl;

	return 0;
}
