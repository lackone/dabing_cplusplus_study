#include <iostream>
#include <mutex>
#include <list>
#include <functional>
#include <condition_variable>

using namespace std;

/**
condition_variable����Ҫ���std::unique_lock<std::mutex>����wait������Ҳ���������̵߳Ĳ�����
condition_variable_any�����Ժ��������lock()��unlock()�����mutex����ʹ�ã�Ҳ����˵�����֣�
	std::mutex����ռ�ķǵݹ黥����
	std::timed_mutex������ʱ�Ķ�ռ�ǵݹ黥����
	std::recursive_mutex��������ʱ���ܵĵݹ黥����
	std::recursive_timed_mutex������ʱ�ĵݹ黥����
 */

 //condition_variable�ĳ�Ա������Ҫ��Ϊ�����֣��̵߳ȴ������������� ���߳�֪ͨ�����ѣ�����

 //wait()
 //wait_for()
 //wait_until()

 //notify_one()������һ������ǰ���������������߳�
 //notify_all()������ȫ������ǰ���������������߳�

class SyncQueue
{
public:
	SyncQueue(int maxSize) : m_maxSize(maxSize) {}

	void put(const int& x)
	{
		unique_lock<mutex> locker(m_mutex);
		// �ж���������ǲ����Ѿ�����
		while (m_queue.size() == m_maxSize)
		{
			cout << "�����������, �����ĵȴ�..." << endl;
			// �����߳�
			m_notFull.wait(locker);
		}
		// ��������뵽���������
		m_queue.push_back(x);
		cout << x << " ������" << endl;
		// ֪ͨ������ȥ����
		m_notEmpty.notify_one();
	}

	int take()
	{
		unique_lock<mutex> locker(m_mutex);
		while (m_queue.empty())
		{
			cout << "��������ѿգ������ĵȴ�������" << endl;
			m_notEmpty.wait(locker);
		}
		// �����������ȡ������(����)
		int x = m_queue.front();
		m_queue.pop_front();
		// ֪ͨ������ȥ����
		m_notFull.notify_one();
		cout << x << " ������" << endl;
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
	list<int> m_queue;     // �洢��������
	mutex m_mutex;         // ������
	condition_variable m_notEmpty;   // ��Ϊ�յ���������
	condition_variable m_notFull;    // û��������������
	int m_maxSize;         // ������е�����������
};

class SyncQueue2
{
public:
	SyncQueue2(int maxSize) : m_maxSize(maxSize) {}

	void put(const int& x)
	{
		lock_guard<mutex> locker(m_mutex);
		// �������������߳�
		m_notFull.wait(m_mutex, [this]() {
			return m_queue.size() != m_maxSize;
			});
		// ��������뵽���������
		m_queue.push_back(x);
		cout << x << " ������" << endl;
		// ֪ͨ������ȥ����
		m_notEmpty.notify_one();
	}

	int take()
	{
		lock_guard<mutex> locker(m_mutex);
		m_notEmpty.wait(m_mutex, [this]() {
			return !m_queue.empty();
			});
		// �����������ȡ������(����)
		int x = m_queue.front();
		m_queue.pop_front();
		// ֪ͨ������ȥ����
		m_notFull.notify_one();
		cout << x << " ������" << endl;
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
	list<int> m_queue;     // �洢��������
	mutex m_mutex;         // ������
	condition_variable_any m_notEmpty;   // ��Ϊ�յ���������
	condition_variable_any m_notFull;    // û��������������
	int m_maxSize;         // ������е�����������
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