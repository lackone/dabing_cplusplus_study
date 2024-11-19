#include <iostream>

using namespace std;

//��C++�������Զ�����࣬��������Ĭ�ϰ�������Ա����һЩ����δ�Զ���ĳ�Ա������
//�޲ι��캯�������������
//�������캯�������������
//�ƶ����캯�������������
//������ֵ�����������ֵ
//�ƶ���ֵ�����������ֵ
//�������������������
//��C++�﷨�����У�һ������Աʵ������Щ�������Զ���汾���������������Ϊ�����Զ�����Ĭ�ϰ汾��

//��C++11��׼�г�= default���εĺ���Ϊ��ʽĬ�ϡ�ȱʡ����explicit defaulted������������=delete���εĺ���Ϊɾ����deleted������������ʾɾ��������

class Base
{
public:
	Base() = default;
	Base(const Base& obj) = default;
	Base(Base&& obj) = default;
	Base& operator= (const Base& obj) = default;
	Base& operator= (Base&& obj) = default;
	~Base() = default;

	// ����д��ȫ�����Ǵ����
	Base(int a = 0) = default;
	Base(int a, int b) = default;
	void print() = default;
	bool operator== (const Base& obj) = default;
	bool operator>=(const Base& obj) = default;
};

class Base2
{
public:
	Base2() = default;
	//=delete ��ʾ��ʾɾ����`��ʽɾ�����Ա����û�ʹ��һЩ��Ӧ��ʹ�õ���ĳ�Ա����`��ʹ�����ַ�ʽ������Ч�ķ�ֹĳЩ����֮���Զ�������ʽ����ת�������Ĵ���
	Base2(const Base2& obj) = delete;
	Base2& operator= (const Base2& obj) = delete;
	//��ֹʹ���Զ��庯��
	void print(char c) = delete;
};

int main()
{
	Base2 b;
	//Base2 tmp1(b);    // error
	//Base2 tmp = b;    // error

	return 0;
}