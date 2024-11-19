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

//在C++的STL容器中，可以进行任意长度的数据的初始化，使用初始化列表也只能进行固定参数的初始化，
//如果想要做到和STL一样有任意长度初始化的能力，可以使用std::initializer_list这个轻量级的类模板来实现。
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