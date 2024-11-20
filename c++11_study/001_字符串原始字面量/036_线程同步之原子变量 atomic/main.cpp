#include <iostream>
#include <thread>
#include <functional>

using namespace std;

//C++11提供了一个原子类型std::atomic<T>，通过这个原子类型管理的内部变量就可以称之为原子变量，我们可以给原子类型指定bool、char、int、long、指针等类型作为模板参数（不支持浮点类型和复合类型）。

//原子操作指的是不会被线程调度机制打断的操作，这种操作一旦开始，就一直运行到结束，中间不会有任何的上下文切换。

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