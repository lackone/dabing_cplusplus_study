#include <iostream>

using namespace std;

//����Խ������͵ȼ�Խ�ߣ����� long long int �ĵȼ������int��
//������ͬ������£���׼���͵ĵȼ�������չ���ͣ����� long long int �� int64 �������64 λ���ȣ���long long int ���͵ĵȼ����ߡ�
//��ͬ��С���з������ͺ��޷������͵ĵȼ���ͬ��long long int ��unsigned long long int �ĵȼ�����ͬ��
//ת�������У��͵ȼ�������Ҫת��Ϊ�ߵȼ����ͣ��з��ŵ���Ҫת��Ϊ�޷������Ρ�
int main()
{
	//�з���
	long num = 100L;
	//��Ӧ���͵���ֵ����ʹ�� LL (��д) ���� ll (Сд) ��׺
	//signed long long
	//long long int
	//signed long long int
	long long num1 = 100LL;
	//��Ӧ���͵���ֵ����ʹ�� ULL (��д) ���� ull (Сд) ���� Ull��uLL (�ȴ�Сд���)��׺
	unsigned long long num2 = 1000ULL;

	//ռ���ڴ�������8�ֽ�
	cout << LLONG_MAX << " " << LLONG_MIN << endl;

	cout << ULLONG_MAX << " " << endl;

	//char       1�ֽ�
	//short int  2�ֽ�
	//int        4�ֽ�
	//long int   32λ4�ֽڣ�64λ8�ֽ�
	//long long int ����8�ֽ�
	//��ʽ����ת�����ӵ��ֽ�ת�������ֽ�ת��

	//�Զ�������
	typedef int myint;
	myint a = 5;

	//�з���ת�����޷�������

	return 0;
}