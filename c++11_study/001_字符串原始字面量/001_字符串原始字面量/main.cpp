#include <iostream>

using namespace std;

// R"xxx()xxx" 原始字面量
// 在R "xxx(raw string)xxx" 中，原始字符串必须用括号（）括起来，括号的前后可以加其他字符串，所加的字符串会被忽略，并且加的字符串必须在括号两边同时出现。
int main()
{
	// 通过 \ 来进行转义字符
	string str = "D:\\test\\test\\test.txt";
	cout << str << endl;

	// 跨行需要通过 \ 来进行拼接
	string str2 = "<html> \
		<title> \
		你好 \
		</title> \
		</html>";
	cout << str2 << endl;

	// R"(原始字符串)" 不作任何转义
	string str3 = R"(D:\test\test\test.txt)";
	cout << str3 << endl;

	// 可以多行
	string str4 = R"(<html>
		<title>
		你好
		</html>
	)";
	cout << str4 << endl;

	return 0;
}