#include <iostream>
#include <cassert>

using namespace std;

//ʹ���˶���assert(expression) ������һ���꣬���Ĳ�����һ�����ʽ��������ʽͨ������һ���������͵�ֵ������Ҫ����ʽ����Ϊ true ������ܼ�������ִ�У������ֱ���жϡ�
char* newChar(size_t size)
{
	//assert��һ������ʱ���ԣ�Ҳ����˵��ֻ���ڳ�������ʱ����������
	assert(size > 0);
	char* p = new char[size];
	return p;
}

int main()
{
	//��̬����static_assert����ν��̬�����ڱ���ʱ���ܹ����м��Ķ�
	static_assert(sizeof(void*) == 4, "����32λ");
	static_assert(sizeof(void*) == 8, "����64λ");

	cout << sizeof(int) << endl;
	cout << sizeof(long) << endl;


	char* p = newChar(0);

	strcpy_s(p, 16, "test");

	cout << p << endl;

	delete[] p;

	return 0;
}