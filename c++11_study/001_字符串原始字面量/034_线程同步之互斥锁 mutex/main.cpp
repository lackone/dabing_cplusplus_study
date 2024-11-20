#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//std::mutex：独占的互斥锁，不能递归使用
//std::timed_mutex：带超时的独占互斥锁，不能递归使用
//std::recursive_mutex：递归互斥锁，不带超时功能
//std::recursive_timed_mutex：带超时的递归互斥锁

int g_num = 0;  // 为 g_num_mutex 所保护
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

//lock_guard是C++11新增的一个模板类，使用这个类，可以简化互斥锁lock()和unlock()的写法
void slow_increment2(int id)
{
	for (int i = 0; i < 3; ++i)
	{
		// 使用哨兵锁管理互斥锁
		lock_guard<mutex> lock(g_num_mutex);

		++g_num;
		cout << id << " => " << g_num << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
}

//递归互斥锁std::recursive_mutex允许同一线程多次获得互斥锁，可以用来解决同一线程需要多次获取互斥量时死锁的问题
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

//std::timed_mutex是超时独占互斥锁，主要是在获取互斥锁资源时增加了超时等待功能，因为不知道获取锁资源需要等待多长时间，
//为了保证不一直等待下去，设置了一个超时时长，超时后线程就可以解除阻塞去做其他事情了。
//std::timed_mutex比std::_mutex多了两个成员函数：try_lock_for()和try_lock_until()：
timed_mutex g_mutex;

void work()
{
	chrono::seconds timeout(1);
	while (true)
	{
		// 通过阻塞一定的时长来争取得到互斥锁所有权
		if (g_mutex.try_lock_for(timeout))
		{
			cout << "当前线程ID: " << this_thread::get_id()
				<< ", 得到互斥锁所有权..." << endl;
			// 模拟处理任务用了一定的时长
			this_thread::sleep_for(chrono::seconds(10));
			// 互斥锁解锁
			g_mutex.unlock();
			break;
		}
		else
		{
			cout << "当前线程ID: " << this_thread::get_id()
				<< ", 没有得到互斥锁所有权..." << endl;
			// 模拟处理其他任务用了一定的时长
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