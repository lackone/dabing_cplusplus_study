#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//std::mutex����ռ�Ļ����������ܵݹ�ʹ��
//std::timed_mutex������ʱ�Ķ�ռ�����������ܵݹ�ʹ��
//std::recursive_mutex���ݹ黥������������ʱ����
//std::recursive_timed_mutex������ʱ�ĵݹ黥����

int g_num = 0;  // Ϊ g_num_mutex ������
mutex g_num_mutex;

void slow_increment(int id)
{
	for (int i = 0; i < 3; ++i)
	{
		g_num_mutex.lock();
		++g_num;
		cout << id << " => " << g_num << endl;
		g_num_mutex.unlock();

		this_thread::sleep_for(chrono::seconds(1));
	}
}

//lock_guard��C++11������һ��ģ���࣬ʹ������࣬���Լ򻯻�����lock()��unlock()��д��
void slow_increment2(int id)
{
	for (int i = 0; i < 3; ++i)
	{
		// ʹ���ڱ�����������
		lock_guard<mutex> lock(g_num_mutex);

		++g_num;
		cout << id << " => " << g_num << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
}

//�ݹ黥����std::recursive_mutex����ͬһ�̶߳�λ�û������������������ͬһ�߳���Ҫ��λ�ȡ������ʱ����������
struct Calculate
{
	Calculate() : m_i(6) {}

	void mul(int x)
	{
		lock_guard<recursive_mutex> locker(m_mutex);
		m_i *= x;
	}

	void div(int x)
	{
		lock_guard<recursive_mutex> locker(m_mutex);
		m_i /= x;
	}

	void both(int x, int y)
	{
		lock_guard<recursive_mutex> locker(m_mutex);
		mul(x);
		div(y);
	}

	int m_i;
	recursive_mutex m_mutex;
};

//std::timed_mutex�ǳ�ʱ��ռ����������Ҫ���ڻ�ȡ��������Դʱ�����˳�ʱ�ȴ����ܣ���Ϊ��֪����ȡ����Դ��Ҫ�ȴ��೤ʱ�䣬
//Ϊ�˱�֤��һֱ�ȴ���ȥ��������һ����ʱʱ������ʱ���߳̾Ϳ��Խ������ȥ�����������ˡ�
//std::timed_mutex��std::_mutex����������Ա������try_lock_for()��try_lock_until()��
timed_mutex g_mutex;

void work()
{
	chrono::seconds timeout(1);
	while (true)
	{
		// ͨ������һ����ʱ������ȡ�õ�����������Ȩ
		if (g_mutex.try_lock_for(timeout))
		{
			cout << "��ǰ�߳�ID: " << this_thread::get_id()
				<< ", �õ�����������Ȩ..." << endl;
			// ģ�⴦����������һ����ʱ��
			this_thread::sleep_for(chrono::seconds(10));
			// ����������
			g_mutex.unlock();
			break;
		}
		else
		{
			cout << "��ǰ�߳�ID: " << this_thread::get_id()
				<< ", û�еõ�����������Ȩ..." << endl;
			// ģ�⴦��������������һ����ʱ��
			this_thread::sleep_for(chrono::milliseconds(50));
		}
	}
}

int main()
{
	thread t1(slow_increment, 0);
	thread t2(slow_increment, 1);
	t1.join();
	t2.join();

	thread t3(slow_increment2, 0);
	thread t4(slow_increment2, 1);
	t3.join();
	t4.join();

	Calculate cal;
	cal.both(6, 3);
	cout << "cal.m_i = " << cal.m_i << endl;

	thread t5(work);
	thread t6(work);

	t5.join();
	t6.join();

	return 0;
}