#include <iostream>
#include <thread>
#include <functional>

using namespace std;

//C++11�ṩ��һ��ԭ������std::atomic<T>��ͨ�����ԭ�����͹�����ڲ������Ϳ��Գ�֮Ϊԭ�ӱ��������ǿ��Ը�ԭ������ָ��bool��char��int��long��ָ���������Ϊģ���������֧�ָ������ͺ͸������ͣ���

//ԭ�Ӳ���ָ���ǲ��ᱻ�̵߳��Ȼ��ƴ�ϵĲ��������ֲ���һ����ʼ����һֱ���е��������м䲻�����κε��������л���

struct Counter
{
	void increment()
	{
		for (int i = 0; i < 10; ++i)
		{
			m_value++;
			cout << "increment number: " << m_value
				<< ", theadID: " << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

	void decrement()
	{
		for (int i = 0; i < 10; ++i)
		{
			m_value--;
			cout << "decrement number: " << m_value
				<< ", theadID: " << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
	// atomic<int> == atomic_int
	atomic_int m_value = 0;
};


int main()
{
	Counter c;
	auto increment = bind(&Counter::increment, &c);
	auto decrement = bind(&Counter::decrement, &c);
	thread t1(increment);
	thread t2(decrement);

	t1.join();
	t2.join();

	return 0;
}