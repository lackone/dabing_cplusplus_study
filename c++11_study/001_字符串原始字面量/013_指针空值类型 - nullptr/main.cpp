#include <iostream>

using namespace std;

void func(char* p)
{
	cout << "func(char* p)" << endl;
}

void func(int p)
{
	cout << "func(int p)" << endl;
}

int main()
{
	//C++98/03 ��׼�У���һ��ָ���ʼ��Ϊ��ָ��ķ�ʽ�� 2 �֣�

	char* p = 0;
	char* p2 = NULL;

	//��C++��NULL��0�ǵȼ۵�
	//���õĶ��� void func(int p)
	func(NULL);
	func(222);

	//C++11 ��׼��û�ж� NULL �ĺ궨�����κ��޸ģ���������¯�������һ���µĹؼ���nullptr
	int* p3 = nullptr;
	char* p4 = nullptr;
	double* p5 = nullptr;

	//nullptr �޷���ʽת��Ϊ���Σ����ǿ�����ʽƥ��ָ�����͡��� C++11 ��׼�£���� NULL �� 0��ʹ�� nullptr ��ʼ����ָ����������Ǳ�д�ĳ�����ӽ�׳
	func(nullptr); //����func(char* p)
	func(333);

	return 0;
}
