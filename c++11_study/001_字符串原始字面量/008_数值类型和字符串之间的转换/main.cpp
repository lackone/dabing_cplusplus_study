#include <iostream>
#include <string>

using namespace std;

//使用to_string()方法可以非常方便地将各种数值类型转换为字符串类型

//如果字符串中所有字符都是数值类型，整个字符串会被转换为对应的数值，并通过返回值返回
//如果字符串的前半部分字符是数值类型，后半部不是，那么前半部分会被转换为对应的数值，并通过返回值返回
//如果字符第一个字符不是数值类型转换失败
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