#include <iostream>

using namespace std;

class Tom;
using Tom2 = Tom;

//声明一个类为另外一个类的友元时，不再需要使用class关键字，并且还可以使用类的别名（使用 typedef 或者 using 定义）。

class Jack
{
	//friend class Tom;  // C++98 标准语法

	friend Tom;  // C++11 标准语法 
};

class Lucy
{
	// friend class Tom; // C++98 标准语法
	friend Tom2; // C++11 标准语法 
};

//为类模板声明友元
template<typename T>
class Person
{
	friend T;
};

template<typename T>
class Rectangle
{
public:
	friend T;
	Rectangle(int w, int h) : width(w), height(h) {}
private:
	int width;
	int height;
};

template<typename T>
class Circle
{
public:
	friend T;
	Circle(int r) : radius(r) {}
private:
	int radius;
};

// 校验类
class Verify
{
public:
	void verifyRectangle(Rectangle<Verify>& r)
	{
		cout << r.width << r.height << endl;
	}

	void verifyCircle(Circle<Verify>& c)
	{
		cout << c.radius << endl;
	}
};

int main()
{
	Person<Tom> p;
	Person<int> pp;

	Verify v;
	Circle<Verify> circle(30);
	Rectangle<Verify> rect(90, 100);
	v.verifyCircle(circle);
	v.verifyRectangle(rect);

	return 0;
}