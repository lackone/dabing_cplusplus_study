#include <iostream>

using namespace std;

class Tom;
using Tom2 = Tom;

//����һ����Ϊ����һ�������Ԫʱ��������Ҫʹ��class�ؼ��֣����һ�����ʹ����ı�����ʹ�� typedef ���� using ���壩��

class Jack
{
	//friend class Tom;  // C++98 ��׼�﷨

	friend Tom;  // C++11 ��׼�﷨ 
};

class Lucy
{
	// friend class Tom; // C++98 ��׼�﷨
	friend Tom2; // C++11 ��׼�﷨ 
};

//Ϊ��ģ��������Ԫ
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

// У����
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