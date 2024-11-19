#include <iostream>

using namespace std;

//�κη��������Ͷ����Գ�Ϊ����������ݳ�Ա���������������֮Ϊ�����������壨Unrestricted Union��

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

	//һ������£�ʹ��new����ռ�ʱ���Ǵ�ϵͳ�Ķѣ�heap���з���ռ䣬�������õĿռ��λ���Ǹ��ݵ�ʱ���ڴ��ʵ��ʹ����������ġ�
	//���ǣ���ĳЩ��������£�������Ҫ���ѷ�����ض��ڴ洴���������ֲ����ͽ���placement new����λ���� new��
	//ClassName* ptr = new (��λ���ڴ��ַ)ClassName;

	int n = 100;
	Base* b = new (&n)Base;
	b->print();

	return 0;
}