#include <iostream>

using namespace std;

//长度越大的整型等级越高，比如 long long int 的等级会高于int。
//长度相同的情况下，标准整型的等级高于扩展类型，比如 long long int 和 int64 如果都是64 位长度，则long long int 类型的等级更高。
//相同大小的有符号类型和无符号类型的等级相同，long long int 和unsigned long long int 的等级就相同。
//转换过程中，低等级整型需要转换为高等级整型，有符号的需要转换为无符号整形。
int main()
{
	//有符号
	long num = 100L;
	//对应类型的数值可以使用 LL (大写) 或者 ll (小写) 后缀
	//signed long long
	//long long int
	//signed long long int
	long long num1 = 100LL;
	//对应类型的数值可以使用 ULL (大写) 或者 ull (小写) 或者 Ull、uLL (等大小写混合)后缀
	unsigned long long num2 = 1000ULL;

	//占用内存最少是8字节
	cout << LLONG_MAX << " " << LLONG_MIN << endl;

	cout << ULLONG_MAX << " " << endl;

	//char       1字节
	//short int  2字节
	//int        4字节
	//long int   32位4字节，64位8字节
	//long long int 最少8字节
	//隐式类型转换，从低字节转换到高字节转换

	//自定义类型
	typedef int myint;
	myint a = 5;

	//有符号转换成无符号类型

	return 0;
}