#include <iostream>

using namespace std;

template<typename T = int, T t = 100>
class Test
{
public:
	void print()
	{
		cout << t << endl;
	}
};

//C++11������˶Ժ���ģ��Ĭ�ϲ�����֧��
template<typename T = int>
void func(T t)
{
	cout << t << endl;
}

//��������Ƶ�������������ʹ���Ƶ���������
//�������ģ���޷��Ƶ����������ͣ���ô��������ʹ��Ĭ��ģ�����
//����޷��Ƶ���ģ��������Ͳ���û������Ĭ��ģ��������������ͻᱨ��
template<typename T = int, typename N>
T func2(N arg)
{
	return arg;
}

template<typename T, typename U = char>
void func3(T arg1 = 100, U arg2 = 100)
{
	cout << arg1 << " " << arg2 << endl;
}

int main()
{
	//������ģ���������Ĭ�ϲ���ʱ������ģ��ĵ�����ͬһ����ͨ��������������ģ����ԣ��������в�������Ĭ�ϲ�������ʹ��ʱҲ������ģ���������<>��ʵ������
	Test<> test;
	test.print();

	func(100);

	cout << func2(3.14) << endl;

	cout << func2(111) << endl;

	func3('a'); //�Ƶ�T=char,Ĭ��U=char
	func3(97, 'a'); //�Ƶ�T=int,�Ƶ�U=char
	//func(); //�޷��Ƶ���Ҳû��Ĭ��

	return 0;
}