#include <iostream>
#include <vector>
#include <map>

using namespace std;


/*
C++98/03中普通的for循环，语法格式：

for(表达式 1; 表达式 2; 表达式 3)
{
	// 循环体
}

C++11基于范围的for循环，语法格式：

for (declaration : expression)
{
	// 循环体
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
		//使用普通的for循环方式（基于迭代器）遍历关联性容器， auto自动推导出的是一个迭代器类型，需要使用迭代器的方式取出元素中的键值对（和指针的操作方法相同）
		cout << it->first << " " << it->second << endl;
	}

	for (auto v : m)
	{
		//使用基于范围的for循环遍历关联性容器，auto自动推导出的类型是容器中的value_type，相当于一个对组（std::pair）对象，提取键值对的方式如下
		cout << v.first << " " << v.second << endl;
	}

	//getVec()只会调用一次
	//对应基于范围的for循环来说，冒号后边的表达式只会被执行一次。
	// 在得到遍历对象之后会先确定好迭代的范围，基于这个范围直接进行遍历。如果是普通的for循环，在每次迭代的时候都需要判断是否已经到了结束边界。
	for (auto v : getVec())
	{
		cout << v << endl;
	}

	return 0;
}