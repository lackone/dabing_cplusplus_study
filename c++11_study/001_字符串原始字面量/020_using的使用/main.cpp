#include <iostream>

using namespace std;

//��C++��using�������������ռ䣬ʹ�������ռ�Ҳ���Է�ֹ������ͻ��

//1. �������
//typedef �ɵ������� �µ�������;
typedef unsigned int uint_t;

//using �µ����� = �ɵ�����;
using uint_t = int;

//2. ģ��ı���

template <typename T>
// ���������
struct MyMap
{
	typedef map<int, T> type;
};

template <typename T>
using mymap = map<int, T>;

void test()
{
	cout << "test" << endl;
}

using test2 = void(*)();

//using�﷨��typedefһ���������ᴴ�����µ����ͣ�����ֻ�Ǹ�ĳЩ���Ͷ������µı�����
// using�����typedef���������ڶ��庯��ָ�����ʱ����������ֱ�ۣ����ҿ��Ը�ģ�嶨�������
int main()
{
	test2 t;
	t = test;
	t();

	return 0;
}