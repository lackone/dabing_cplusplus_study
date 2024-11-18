#include <iostream>
#include <map>

using namespace std;

template<typename T>
class Container
{
public:
	void print(T& t)
	{
		auto it = t.begin();
		for (; it != t.end(); it++)
		{
			cout << it->first << "," << it->second << endl;
		}
	}
};

//C++11改进了编译器的解析规则，尽可能地将多个右尖括号（>）解析成模板参数结束符
int main()
{
	map<int, string> m;
	m.insert(make_pair(1, "aaa"));
	m.insert(make_pair(2, "bbb"));

	//连续的两个右尖括号（>>）会被编译器解析成右移操作符
	Container<map<int, string>> c;
	c.print(m);

	return 0;
}
