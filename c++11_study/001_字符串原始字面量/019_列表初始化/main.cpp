#include <iostream>

using namespace std;

void traversal(std::initializer_list<int> a)
{
	for (auto it = a.begin(); it != a.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

class Test
{
public:
	Test(int) {}
private:
	Test(const Test&);
};

//��C++��STL�����У����Խ������ⳤ�ȵ����ݵĳ�ʼ����ʹ�ó�ʼ���б�Ҳֻ�ܽ��й̶������ĳ�ʼ����
//�����Ҫ������STLһ�������ⳤ�ȳ�ʼ��������������ʹ��std::initializer_list�������������ģ����ʵ�֡�
int main()
{
	Test t1(520);
	Test t2 = 520;
	Test t3 = { 520 };
	Test t4{ 520 };
	int a1 = { 1314 };
	int a2{ 1314 };
	int arr1[] = { 1, 2, 3 };
	int arr2[]{ 1, 2, 3 };

	traversal({ 2, 4, 6, 8, 0 });

	return 0;
}