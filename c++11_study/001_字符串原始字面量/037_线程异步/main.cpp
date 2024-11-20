#include <iostream>
#include <thread>
#include <future>

using namespace std;

//C++11中增加的线程类，使得我们能够非常方便的创建和使用线程，但有时会有些不方便，比如需要获取线程返回的结果，
//就不能通过join()得到结果，只能通过一些额外手段获得，比如：定义一个全局变量，在子线程中赋值，在主线程中读这个变量的值，整个过程比较繁琐。C++提供的线程库中提供了一些类用于访问异步操作的结果。

int main()
{
	promise<int> pr;
	thread t1([](promise<int>& p) {
		//存储要传出的 value 值，并立即让状态就绪
		p.set_value(100);
		this_thread::sleep_for(chrono::seconds(3));
		cout << "睡醒了...." << endl;
		}, ref(pr));

	future<int> f = pr.get_future();
	int value = f.get();
	cout << "value: " << value << endl;

	t1.join();

	promise<int> pr2;
	thread t2([](promise<int>& p) {
		//子线程任务函数执行结束，让状态就绪
		//存储要传出的 value 值，但是不立即令状态就绪。在当前线程退出时，子线程资源被销毁，再令状态就绪。
		p.set_value_at_thread_exit(100);
		this_thread::sleep_for(chrono::seconds(3));
		cout << "睡醒了...." << endl;
		}, ref(pr2));

	future<int> f2 = pr2.get_future();
	int value2 = f2.get();
	cout << "value: " << value2 << endl;

	t2.join();


	//packaged_task其实就是对子线程要执行的任务函数进行了包装，和可调用对象包装器的使用方法相同，包装完毕之后直接将包装得到的任务对象传递给线程对象就可以了。
	packaged_task<int(int)> task([](int x) {
		return x += 100;
		});

	thread t3(ref(task), 100);

	future<int> f3 = task.get_future();
	int value3 = f3.get();
	cout << "value: " << value3 << endl;

	t3.join();

	//调用async()函数直接创建线程执行任务
	cout << "主线程ID: " << this_thread::get_id() << endl;
	// 调用函数直接创建线程执行任务
	future<int> f4 = async([](int x) {
		cout << "子线程ID: " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::seconds(5));
		return x += 100;
		}, 100);

	future_status status;
	do {
		status = f4.wait_for(chrono::seconds(1));
		if (status == future_status::deferred)
		{
			cout << "线程还没有执行..." << endl;
			f4.wait();
		}
		else if (status == future_status::ready)
		{
			cout << "子线程返回值: " << f4.get() << endl;
		}
		else if (status == future_status::timeout)
		{
			cout << "任务还未执行完毕, 继续等待..." << endl;
		}
	} while (status != future_status::ready);


	//调用async()函数不创建线程执行任务
	cout << "主线程ID: " << this_thread::get_id() << endl;
	// 调用函数直接创建线程执行任务
	future<int> f5 = async(launch::deferred, [](int x) {
		cout << "子线程ID: " << this_thread::get_id() << endl;
		return x += 100;
		}, 100);

	this_thread::sleep_for(chrono::seconds(5));
	cout << f5.get();


	return 0;
}