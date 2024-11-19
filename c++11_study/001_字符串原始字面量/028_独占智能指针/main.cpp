#include <iostream>
#include <memory>

using namespace std;

int main()
{
	unique_ptr<int> ptr1(new int(10));

	//不允许将一个unique_ptr赋值给另一个unique_ptr
	//unique_ptr<int> ptr2 = ptr1;

	// 通过转移所有权的方式初始化
	unique_ptr<int> ptr2 = move(ptr1);

	//ptr1.reset();解除对原始内存的管理
	//ptr2.reset(new int(250)); 重新指定智能指针管理的原始内存

	ptr1.reset();
	ptr2.reset(new int(250));

	//获取独占智能指针管理的原始地址
	cout << *ptr2.get() << endl;

	//unique_ptr指定删除器和shared_ptr指定删除器是有区别的，unique_ptr指定删除器的时候需要确定删除器的类型，所以不能像shared_ptr那样直接指定删除器

	using func_ptr = void(*)(int*);
	unique_ptr<int, func_ptr> ptr3(new int(10), [](int* p) {delete p; });

	return 0;
}