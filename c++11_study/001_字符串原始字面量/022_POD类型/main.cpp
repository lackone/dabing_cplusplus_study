#include <iostream>

using namespace std;

void trivial()
{
	class A {};
	class B { B() {} };
	class C : B {};
	class D { virtual void fn() {} };
	class E : virtual public A { };

	cout << std::boolalpha;
	cout << "is_trivial:" << std::endl;
	cout << "int: " << is_trivial<int>::value << endl;
	cout << "A: " << is_trivial<A>::value << endl;
	cout << "B: " << is_trivial<B>::value << endl;
	cout << "C: " << is_trivial<C>::value << endl;
	cout << "D: " << is_trivial<D>::value << endl;
	cout << "E: " << is_trivial<E>::value << endl;
}

struct A { };
struct B : A { int j; };
struct C
{
public:
	int a;
private:
	int c;
};
struct D1 { static int i; };
struct D2 { int i; };
struct E1 { static int i; };
struct E2 { int i; };
struct D : public D1, public E1 { int a; };
struct E : public D1, public E2 { int a; };
struct F : public D2, public E2 { static int a; };
struct G : public A
{
	int foo;
	A a;
};
struct H : public A
{
	A a;
	int foo;
};

int main()
{
	//POD是英文中 Plain Old Data 的缩写，翻译过来就是普通的旧数据 
	//通常用于说明一个类型的属性，尤其是用户自定义类型的属性。

	trivial();

	cout << std::boolalpha;
	cout << "is_standard_layout:" << std::endl;
	cout << "A: " << is_standard_layout<A>::value << endl;
	cout << "B: " << is_standard_layout<B>::value << endl;
	cout << "C: " << is_standard_layout<C>::value << endl;
	cout << "D: " << is_standard_layout<D>::value << endl;
	cout << "D1: " << is_standard_layout<D1>::value << endl;
	cout << "E: " << is_standard_layout<E>::value << endl;
	cout << "F: " << is_standard_layout<F>::value << endl;
	cout << "G: " << is_standard_layout<G>::value << endl;
	cout << "H: " << is_standard_layout<H>::value << endl;

	return 0;
}