#include <iostream>
#include <string>

using namespace std;

//ʹ��to_string()�������Էǳ�����ؽ�������ֵ����ת��Ϊ�ַ�������

//����ַ����������ַ�������ֵ���ͣ������ַ����ᱻת��Ϊ��Ӧ����ֵ����ͨ������ֵ����
//����ַ�����ǰ�벿���ַ�����ֵ���ͣ���벿���ǣ���ôǰ�벿�ֻᱻת��Ϊ��Ӧ����ֵ����ͨ������ֵ����
//����ַ���һ���ַ�������ֵ����ת��ʧ��
int main()
{
	string str = to_string(3.14);

	cout << typeid(str).name() << endl;

	int a = stoi("123");
	long b = stol("123");
	long long c = stoll("12345678");
	unsigned long d = stoul("222");
	unsigned long e = stoull("222222222");
	float f = stof("3.14");
	double g = stod("3.1415926");
	long double h = stold("3.1415926");

	return 0;
}