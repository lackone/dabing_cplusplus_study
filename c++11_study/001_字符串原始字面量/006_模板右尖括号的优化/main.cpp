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

//C++11�Ľ��˱������Ľ������򣬾����ܵؽ�����Ҽ����ţ�>��������ģ�����������
int main()
{
	map<int, string> m;
	m.insert(make_pair(1, "aaa"));
	m.insert(make_pair(2, "bbb"));

	//�����������Ҽ����ţ�>>���ᱻ���������������Ʋ�����
	Container<map<int, string>> c;
	c.print(m);

	return 0;
}
