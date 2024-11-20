#include <iostream>
#include <thread>

using namespace std;

//在C++11中不仅添加了线程类，还添加了一个关于线程的命名空间std::this_thread

//std::this_thread中的get_id()方法可以得到当前线程的线程ID

//this_thread中提供了一个休眠函数sleep_for()，调用这个函数的线程会马上从运行态变成阻塞态并在这种状态下休眠一定的时长，因为阻塞态的线程已经让出了CPU资源

//命名空间this_thread中提供了另一个休眠函数sleep_until()
//sleep_until()：指定线程阻塞到某一个指定的时间点time_point类型，之后解除阻塞
//sleep_for()：指定线程阻塞一定的时间长度duration 类型，之后解除阻塞

//命名空间this_thread中提供了一个非常绅士的函数yield()，在线程中调用这个函数之后，处于运行态的线程会主动让出自己已经抢到的CPU时间片，最终变为就绪态，
//这样其它的线程就有更大的概率能够抢到CPU时间片了。


void func()
{
	cout << "子线程: " << this_thread::get_id() << endl;
}

void func2()
{
	for (int i = 0; i < 10; ++i)
	{
		this_thread::sleep_for(chrono::seconds(1));
		cout << "子线程: " << this_thread::get_id() << ", i = " << i << endl;
	}
}

void func3()
{
	for (int i = 0; i < 10; ++i)
	{
		// 获取当前系统时间点
		auto now = chrono::system_clock::now();
		// 时间间隔为2s
		chrono::seconds sec(2);
		// 当前时间点之后休眠两秒
		this_thread::sleep_until(now + sec);
		cout << "子线程: " << this_thread::get_id() << ", i = " << i << endl;
	}
}

void func4()
{
	for (int i = 0; i < 100000000000; ++i)
	{
		cout << "子线程: " << this_thread::get_id() << ", i = " << i << endl;
		this_thread::yield();
	}
}

int main()
{
	cout << "主线程: " << this_thread::get_id() << endl;

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