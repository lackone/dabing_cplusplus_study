#include <iostream>
#include <memory>

using namespace std;

//C++11中提供了三种智能指针，使用这些智能指针时需要引用头文件<memory>：

//std::shared_ptr：共享的智能指针
//std::unique_ptr：独占的智能指针
//std::weak_ptr：弱引用的智能指针，它不共享指针，不能操作资源，是用来监视shared_ptr的。

//共享智能指针是指多个智能指针可以同时管理同一块有效的内存

class Test
{
public:
	Test()
	{
		cout << "construct Test..." << endl;
	}
	Test(int x)
	{
		cout << "construct Test, x = " << x << endl;
	}
	Test(string str)
	{
		cout << "construct Test, str = " << str << endl;
	}
	~Test()
	{
		cout << "destruct Test ..." << endl;
	}
};

void delPtr(int* p)
{
	delete p;
	cout << "int 型内存被释放了..." << endl;
}

int main()
{
	//通过构造函数初始化
	shared_ptr<int> p1(new int(100));
	cout << p1.use_count() << endl; //引用计数

	shared_ptr<char> p2(new char[10]);
	cout << p2.use_count() << endl;

	shared_ptr<int> p3;
	cout << p3.use_count() << endl;

	shared_ptr<int> p4(nullptr);
	cout << p4.use_count() << endl;

	//不要使用一个原始指针初始化多个shared_ptr。
	//int* pp = new int;
	//shared_ptr<int> pp1(pp);
	//shared_ptr<int> pp2(pp);

	//通过拷贝和移动构造函数初始化
	shared_ptr<int> p5(new int(300));
	cout << p5.use_count() << endl;
	shared_ptr<int> p6(p5);
	cout << p6.use_count() << endl;
	shared_ptr<int> p7 = p5;
	cout << p7.use_count() << endl;
	shared_ptr<int> p8(std::move(p5));
	cout << p8.use_count() << endl;
	std::shared_ptr<int> p9 = std::move(p6);
	cout << p9.use_count() << endl;

	//通过std::make_shared初始化
	shared_ptr<int> ptr1 = make_shared<int>(520);
	shared_ptr<Test> ptr2 = make_shared<Test>();
	shared_ptr<Test> ptr3 = make_shared<Test>(520);
	shared_ptr<Test> ptr4 = make_shared<Test>("test");

	//通过 reset 方法初始化

	shared_ptr<int> ptr5;
	ptr5.reset(new int(250));
	cout << ptr5.use_count() << endl;

	//获取原始指针
	shared_ptr<char> pstr(new char[32]);
	char* str = pstr.get();
	memset(str, 0, 32);
	strcpy_s(str, 32, "test");
	cout << str << endl;

	//指定删除器
	shared_ptr<int> ptr(new int(250), delPtr);

	return 0;
}