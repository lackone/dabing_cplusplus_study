#include <iostream>

using namespace std;

class Test
{
public:
	Test()
	{

	}
};

template<typename T>
void printValue(T& t)
{
	cout << "lvalue" << t << endl;
}

template<typename T>
void printValue(T&& t)
{
	cout << "rvalue" << t << endl;
}

//��TΪ��ֵ��������ʱ��t����ת��ΪT���͵���ֵ
//��T������ֵ��������ʱ��t����ת��ΪT���͵���ֵ
template<typename T>
void testForward(T&& v)
{
	printValue(v);
	printValue(move(v));
	printValue(forward<T>(v));
	cout << endl;
}

int main()
{
	//ʹ��std::move�������Խ���ֵת��Ϊ��ֵ��ʹ����������������ƶ��κζ��������Ǻ��ƶ����캯��һ���������ƶ����壬�������״̬��������Ȩ��һ������ת�Ƶ���һ������ֻ��ת�ƣ�û���ڴ濽����

	Test t;
	//Test&& t1 = t; //t����ֵ
	Test&& t2 = move(t); //ʹ��move()��������ֵת��Ϊ����ֵ�������Ϳ��Գ�ʼ����ֵ�����ˡ�

	testForward(520);
	int num = 1314;
	testForward(num);
	testForward(forward<int>(num));
	testForward(forward<int&>(num));
	testForward(forward<int&&>(num));

	return 0;
}