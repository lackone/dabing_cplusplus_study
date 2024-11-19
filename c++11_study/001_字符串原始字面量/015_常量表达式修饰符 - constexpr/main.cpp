#include <iostream>

using namespace std;

struct Test
{
	int id;
	int num;
};

//1����������Ҫ�з���ֵ������return ���صı��ʽ�����ǳ������ʽ��
//2��������ʹ��֮ǰ�������ж�Ӧ�Ķ�����䡣
//3�����������ĺ������У����ܳ��ַǳ������ʽ֮�����䣨using ָ�typedef ����Լ� static_assert ���ԡ�return�����⣩��

// error�����ǳ������ʽ����
constexpr void func1()
{
	int a = 100;
	cout << "a: " << a << endl;
}

// error�����ǳ������ʽ����
constexpr int func1()
{
	int a = 100;
	return a;
}

class A
{
public:
	//���Ա����
	constexpr int func()
	{
		constexpr int v = 100;
		return 5 * v;
	}
};

struct Person
{
	const char* name;
	int age;
};

//����ģ�庯��
template<typename T>
constexpr T display(T t)
{
	return t;
}

struct Person2
{
	//���캯���ĺ��������Ϊ�գ����ұ�����ó�ʼ���б�ķ�ʽΪ������Ա��ֵ��
	constexpr Person2(const char* p, int age) :name(p), age(age)
	{

	}
	const char* name;
	int age;
};

int main()
{
	//const�ؼ��֣��ӹ�������˵����ؼ�����˫�����壺����ֻ�������γ���
	const int cnt = 10;
	int arr[cnt]; // ok��cnt ��һ������

	//C++11�������һ���µĹؼ���constexpr������ؼ������������γ������ʽ�ġ�
	//��ν�������ʽ��ָ�ľ����ɶ������1��������ֵ����ı䣩��ɲ����ڱ�������о͵õ��������ı��ʽ��

	constexpr int i = 100;
	constexpr int j = i + 200;

	constexpr Test t{ 1, 2 };

	//t.num += 100; //����t��һ��������������ĳ�ԱҲ�ǳ���

	A a;
	constexpr int v = a.func();

	struct Person p { "test", 22 };
	struct Person p2 = display(p); //��ͨ����

	constexpr int ret = display(200); //�������ʽ����

	constexpr struct Person p3 = { "test", 33 };
	constexpr struct Person p4 = display(p3); //�������ʽ����

	return 0;
}