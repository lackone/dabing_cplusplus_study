#include <iostream>
#include <mutex>
#include <list>
#include <functional>
#include <condition_variable>

using namespace std;

/**
condition_variable：需要配合std::unique_lock<std::mutex>进行wait操作，也就是阻塞线程的操作。
condition_variable_any：可以和任意带有lock()、unlock()语义的mutex搭配使用，也就是说有四种：
	std::mutex：独占的非递归互斥锁
	std::timed_mutex：带超时的独占非递归互斥锁
	std::recursive_mutex：不带超时功能的递归互斥锁
	std::recursive_timed_mutex：带超时的递归互斥锁
 */

 //condition_variable的成员函数主要分为两部分：线程等待（阻塞）函数 和线程通知（唤醒）函数

 //wait()
 //wait_for()
 //wait_until()

 //notify_one()：唤醒一个被当前条件变量阻塞的线程
 //notify_all()：唤醒全部被当前条件变量阻塞的线程

class SyncQueue
{
public:
	SyncQueue(int maxSize) : m_maxSize(maxSize) {}

	void put(const int& x)
	{
		unique_lock<mutex> locker(m_mutex);
		// 判断任务队列是不是已经满了
		while (m_queue.size() == m_maxSize)
		{
			cout << "任务队列已满, 请耐心等待..." << endl;
			// 阻塞线程
			m_notFull.wait(locker);
		}
		// 将任务放入到任务队列中
		m_queue.push_back(x);
		cout << x << " 被生产" << endl;
		// 通知消费者去消费
		m_notEmpty.notify_one();
	}

	int take()
	{
		unique_lock<mutex> locker(m_mutex);
		while (m_queue.empty())
		{
			cout << "任务队列已空，请耐心等待。。。" << endl;
			m_notEmpty.wait(locker);
		}
		// 从任务队列中取出任务(消费)
		int x = m_queue.front();
		m_queue.pop_front();
		// 通知生产者去生产
		m_notFull.notify_one();
		cout << x << " 被消费" << endl;
		return x;
	}

	bool empty()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.empty();
	}

	bool full()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.size() == m_maxSize;
	}

	int size()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.size();
	}

private:
	list<int> m_queue;     // 存储队列数据
	mutex m_mutex;         // 互斥锁
	condition_variable m_notEmpty;   // 不为空的条件变量
	condition_variable m_notFull;    // 没有满的条件变量
	int m_maxSize;         // 任务队列的最大任务个数
};

class SyncQueue2
{
public:
	SyncQueue2(int maxSize) : m_maxSize(maxSize) {}

	void put(const int& x)
	{
		lock_guard<mutex> locker(m_mutex);
		// 根据条件阻塞线程
		m_notFull.wait(m_mutex, [this]() {
			return m_queue.size() != m_maxSize;
			});
		// 将任务放入到任务队列中
		m_queue.push_back(x);
		cout << x << " 被生产" << endl;
		// 通知消费者去消费
		m_notEmpty.notify_one();
	}

	int take()
	{
		lock_guard<mutex> locker(m_mutex);
		m_notEmpty.wait(m_mutex, [this]() {
			return !m_queue.empty();
			});
		// 从任务队列中取出任务(消费)
		int x = m_queue.front();
		m_queue.pop_front();
		// 通知生产者去生产
		m_notFull.notify_one();
		cout << x << " 被消费" << endl;
		return x;
	}

	bool empty()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.empty();
	}

	bool full()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.size() == m_maxSize;
	}

	int size()
	{
		lock_guard<mutex> locker(m_mutex);
		return m_queue.size();
	}

private:
	list<int> m_queue;     // 存储队列数据
	mutex m_mutex;         // 互斥锁
	condition_variable_any m_notEmpty;   // 不为空的条件变量
	condition_variable_any m_notFull;    // 没有满的条件变量
	int m_maxSize;         // 任务队列的最大任务个数
};

int main()
{
	SyncQueue taskQ(50);
	auto produce = bind(&SyncQueue::put, &taskQ, placeholders::_1);
	auto consume = bind(&SyncQueue::take, &taskQ);

	thread t1[3];
	thread t2[3];

	for (int i = 0; i < 3; ++i)
	{
		t1[i] = thread(produce, i + 100);
		t2[i] = thread(consume);
	}

	for (int i = 0; i < 3; ++i)
	{
		t1[i].join();
		t2[i].join();
	}

	SyncQueue2 taskQ2(50);
	auto produce2 = bind(&SyncQueue2::put, &taskQ2, placeholders::_1);
	auto consume2 = bind(&SyncQueue2::take, &taskQ2);

	thread t3[3];
	thread t4[3];

	for (int i = 0; i < 3; ++i)
	{
		t3[i] = thread(produce2, i + 100);
		t4[i] = thread(consume2);
	}

	for (int i = 0; i < 3; ++i)
	{
		t3[i].join();
		t4[i].join();
	}

	return 0;
}