#include <iostream>

using namespace std;

struct MyException
{
	MyException(const string& msg) : _msg(msg)
	{

	}
	string _msg;
};

//�����������throw�쳣�ӿ��������������ʾ�����׳����쳣���ͣ��ֱ�Ϊint ��MyException ����
double division(int a, int b) throw(MyException, int)
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

//divisionMethod û������쳣�ӿ���������ʾ�ڸú����п����׳��������͵��쳣
double division2(int a, int b)
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

// �����������throw�쳣�ӿ�������������б�Ϊ�գ���ʾ�ú����������׳��쳣��
double division3(int a, int b) throw()
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

//��ʾ���������׳��쳣�Ķ�̬�쳣���� throw() Ҳ���µ� noexcept �쳣������ȡ��

//�򵥵��ں������������ noexcept �ؼ���

//���Խ���һ���������ʽ��Ϊ������������ʾ��
//double divisionMethod(int a, int b) noexcept(�������ʽ);
//�������ʽ�Ľ���ᱻת����һ��bool���͵�ֵ��
//ֵΪ true����ʾ���������׳��쳣
//ֵΪ false����ʾ�п����׳��쳣����
//�����������ʽ��noexcept�൱��������noexcept��true�����������׳��쳣��

double division4(int a, int b) noexcept
{
	if (b == 0)
	{
		throw MyException("b is zero");
		//throw 100;
	}
	return a / b;
}

int main()
{
	try
	{
		throw - 1;
	}
	catch (int e)
	{
		cout << e << endl;

	}

	try
	{
		double ret = division(2, 0);
		cout << ret << endl;
	}
	catch (const MyException& e)
	{
		cout << e._msg << endl;
	}
	catch (int e)
	{
		cout << e << endl;
	}

	//cout << division3(2, 0) << endl;

	cout << division4(2, 0) << endl;

	return 0;
}