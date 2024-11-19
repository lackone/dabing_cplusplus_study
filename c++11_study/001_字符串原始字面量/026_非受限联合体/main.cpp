#include <iostream>

using namespace std;

//任何非引用类型都可以成为联合体的数据成员，这样的联合体称之为非受限联合体（Unrestricted Union）

union Test
{
	int age;
	long id;
	// int& tmp = age; // error
	static char c;
	static int print()
	{
		cout << "c value: " << c << endl;
		return 0;
	}
};

char Test::c;

class Base
{
public:
	Base() {}
	~Base() {}
	void print()
	{
		cout << "number value: " << number << endl;
	}
private:
	int number;
};

int main()
{
	Test t;
	Test t1;
	t.c = 'b';
	t1.c = 'c';
	t1.age = 666;
	cout << "t.c: " << t.c << endl;
	cout << "t1.c: " << t1.c << endl;
	cout << "t1.age: " << t1.age << endl;
	cout << "t1.id: " << t1.id << endl;
	t.print();
	Test::print();

	//一般情况下，使用new申请空间时，是从系统的堆（heap）中分配空间，申请所得的空间的位置是根据当时的内存的实际使用情况决定的。
	//但是，在某些特殊情况下，可能需要在已分配的特定内存创建对象，这种操作就叫做placement new即定位放置 new。
	//ClassName* ptr = new (定位的内存地址)ClassName;

	int n = 100;
	Base* b = new (&n)Base;
	b->print();

	return 0;
}