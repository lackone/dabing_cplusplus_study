#include <iostream>
#include <thread>

using namespace std;

void func(int num, string str)
{
	for (int i = 0; i < 10; ++i)
	{
		cout << "���߳�: i = " << i << "num: "
			<< num << ", str: " << str << endl;
	}
}

void func1()
{
	for (int i = 0; i < 10; ++i)
	{
		cout << "���߳�: i = " << i << endl;
	}
}

int main()
{
	cout << "���̵߳��߳�ID: " << this_thread::get_id() << endl;
	thread t(func, 520, "i love you");
	thread t1(func1);
	cout << "�߳�t ���߳�ID: " << t.get_id() << endl;
	cout << "�߳�t1���߳�ID: " << t1.get_id() << endl;

	//join()������˼������һ���̣߳���ζ�������صȴ��̵߳���ֹ���߳���������
	t.join();
	t1.join();

	//joinable()���������ж����̺߳����߳��Ƿ�����������ӣ�״̬

	//��ȡ��ǰ�������CPU������
	int num = thread::hardware_concurrency();
	cout << "CPU number: " << num << endl;

	return 0;
}