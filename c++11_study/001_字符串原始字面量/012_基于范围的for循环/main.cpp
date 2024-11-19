#include <iostream>
#include <vector>
#include <map>

using namespace std;


/*
C++98/03����ͨ��forѭ�����﷨��ʽ��

for(���ʽ 1; ���ʽ 2; ���ʽ 3)
{
	// ѭ����
}

C++11���ڷ�Χ��forѭ�����﷨��ʽ��

for (declaration : expression)
{
	// ѭ����
}
*/

vector<int> v{ 1, 2, 3, 4, 5 };

vector<int>& getVec()
{
	cout << "getVec" << endl;
	return v;
}

int main()
{
	vector<int> vec{ 1, 2, 3,4 };

	for (auto v : vec)
	{
		cout << v << endl;
	}

	for (auto& v : vec)
	{
		v++;
		cout << v << endl;
	}

	for (const auto& v : vec)
	{
		cout << v << endl;
	}

	map<int, string> m{
		{1, "111"},
		{2, "222"},
		{3, "333"}
	};

	for (auto it = m.begin(); it != m.end(); it++)
	{
		//ʹ����ͨ��forѭ����ʽ�����ڵ����������������������� auto�Զ��Ƶ�������һ�����������ͣ���Ҫʹ�õ������ķ�ʽȡ��Ԫ���еļ�ֵ�ԣ���ָ��Ĳ���������ͬ��
		cout << it->first << " " << it->second << endl;
	}

	for (auto v : m)
	{
		//ʹ�û��ڷ�Χ��forѭ������������������auto�Զ��Ƶ����������������е�value_type���൱��һ�����飨std::pair��������ȡ��ֵ�Եķ�ʽ����
		cout << v.first << " " << v.second << endl;
	}

	//getVec()ֻ�����һ��
	//��Ӧ���ڷ�Χ��forѭ����˵��ð�ź�ߵı��ʽֻ�ᱻִ��һ�Ρ�
	// �ڵõ���������֮�����ȷ���õ����ķ�Χ�����������Χֱ�ӽ��б������������ͨ��forѭ������ÿ�ε�����ʱ����Ҫ�ж��Ƿ��Ѿ����˽����߽硣
	for (auto v : getVec())
	{
		cout << v << endl;
	}

	return 0;
}