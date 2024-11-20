#include <iostream>
#include <thread>

using namespace std;

//��C++11�в���������߳��࣬�������һ�������̵߳������ռ�std::this_thread

//std::this_thread�е�get_id()�������Եõ���ǰ�̵߳��߳�ID

//this_thread���ṩ��һ�����ߺ���sleep_for()����������������̻߳����ϴ�����̬�������̬��������״̬������һ����ʱ������Ϊ����̬���߳��Ѿ��ó���CPU��Դ

//�����ռ�this_thread���ṩ����һ�����ߺ���sleep_until()
//sleep_until()��ָ���߳�������ĳһ��ָ����ʱ���time_point���ͣ�֮��������
//sleep_for()��ָ���߳�����һ����ʱ�䳤��duration ���ͣ�֮��������

//�����ռ�this_thread���ṩ��һ���ǳ���ʿ�ĺ���yield()�����߳��е����������֮�󣬴�������̬���̻߳������ó��Լ��Ѿ�������CPUʱ��Ƭ�����ձ�Ϊ����̬��
//�����������߳̾��и���ĸ����ܹ�����CPUʱ��Ƭ�ˡ�


void func()
{
	cout << "���߳�: " << this_thread::get_id() << endl;
}

void func2()
{
	for (int i = 0; i < 10; ++i)
	{
		this_thread::sleep_for(chrono::seconds(1));
		cout << "���߳�: " << this_thread::get_id() << ", i = " << i << endl;
	}
}

void func3()
{
	for (int i = 0; i < 10; ++i)
	{
		// ��ȡ��ǰϵͳʱ���
		auto now = chrono::system_clock::now();
		// ʱ����Ϊ2s
		chrono::seconds sec(2);
		// ��ǰʱ���֮����������
		this_thread::sleep_until(now + sec);
		cout << "���߳�: " << this_thread::get_id() << ", i = " << i << endl;
	}
}

void func4()
{
	for (int i = 0; i < 100000000000; ++i)
	{
		cout << "���߳�: " << this_thread::get_id() << ", i = " << i << endl;
		this_thread::yield();
	}
}

int main()
{
	cout << "���߳�: " << this_thread::get_id() << endl;

	thread t(func);
	t.join();

	thread t2(func2);
	t2.join();

	thread t3(func3);
	t3.join();

	thread t4(func4);
	t4.join();

	return 0;
}