#include <iostream>

using namespace std;

// R"xxx()xxx" ԭʼ������
// ��R "xxx(raw string)xxx" �У�ԭʼ�ַ������������ţ��������������ŵ�ǰ����Լ������ַ��������ӵ��ַ����ᱻ���ԣ����Ҽӵ��ַ�����������������ͬʱ���֡�
int main()
{
	// ͨ�� \ ������ת���ַ�
	string str = "D:\\test\\test\\test.txt";
	cout << str << endl;

	// ������Ҫͨ�� \ ������ƴ��
	string str2 = "<html> \
		<title> \
		��� \
		</title> \
		</html>";
	cout << str2 << endl;

	// R"(ԭʼ�ַ���)" �����κ�ת��
	string str3 = R"(D:\test\test\test.txt)";
	cout << str3 << endl;

	// ���Զ���
	string str4 = R"(<html>
		<title>
		���
		</html>
	)";
	cout << str4 << endl;

	return 0;
}