#include <iostream>
#include <thread>
#include <future>

using namespace std;

//C++11�����ӵ��߳��࣬ʹ�������ܹ��ǳ�����Ĵ�����ʹ���̣߳�����ʱ����Щ�����㣬������Ҫ��ȡ�̷߳��صĽ����
//�Ͳ���ͨ��join()�õ������ֻ��ͨ��һЩ�����ֶλ�ã����磺����һ��ȫ�ֱ����������߳��и�ֵ�������߳��ж����������ֵ���������̱ȽϷ�����C++�ṩ���߳̿����ṩ��һЩ�����ڷ����첽�����Ľ����

int main()
{
	promise<int> pr;
	thread t1([](promise<int>& p) {
		//�洢Ҫ������ value ֵ����������״̬����
		p.set_value(100);
		this_thread::sleep_for(chrono::seconds(3));
		cout << "˯����...." << endl;
		}, ref(pr));

	future<int> f = pr.get_future();
	int value = f.get();
	cout << "value: " << value << endl;

	t1.join();

	promise<int> pr2;
	thread t2([](promise<int>& p) {
		//���߳�������ִ�н�������״̬����
		//�洢Ҫ������ value ֵ�����ǲ�������״̬�������ڵ�ǰ�߳��˳�ʱ�����߳���Դ�����٣�����״̬������
		p.set_value_at_thread_exit(100);
		this_thread::sleep_for(chrono::seconds(3));
		cout << "˯����...." << endl;
		}, ref(pr2));

	future<int> f2 = pr2.get_future();
	int value2 = f2.get();
	cout << "value: " << value2 << endl;

	t2.join();


	//packaged_task��ʵ���Ƕ����߳�Ҫִ�е������������˰�װ���Ϳɵ��ö����װ����ʹ�÷�����ͬ����װ���֮��ֱ�ӽ���װ�õ���������󴫵ݸ��̶߳���Ϳ����ˡ�
	packaged_task<int(int)> task([](int x) {
		return x += 100;
		});

	thread t3(ref(task), 100);

	future<int> f3 = task.get_future();
	int value3 = f3.get();
	cout << "value: " << value3 << endl;

	t3.join();

	//����async()����ֱ�Ӵ����߳�ִ������
	cout << "���߳�ID: " << this_thread::get_id() << endl;
	// ���ú���ֱ�Ӵ����߳�ִ������
	future<int> f4 = async([](int x) {
		cout << "���߳�ID: " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::seconds(5));
		return x += 100;
		}, 100);

	future_status status;
	do {
		status = f4.wait_for(chrono::seconds(1));
		if (status == future_status::deferred)
		{
			cout << "�̻߳�û��ִ��..." << endl;
			f4.wait();
		}
		else if (status == future_status::ready)
		{
			cout << "���̷߳���ֵ: " << f4.get() << endl;
		}
		else if (status == future_status::timeout)
		{
			cout << "����δִ�����, �����ȴ�..." << endl;
		}
	} while (status != future_status::ready);


	//����async()�����������߳�ִ������
	cout << "���߳�ID: " << this_thread::get_id() << endl;
	// ���ú���ֱ�Ӵ����߳�ִ������
	future<int> f5 = async(launch::deferred, [](int x) {
		cout << "���߳�ID: " << this_thread::get_id() << endl;
		return x += 100;
		}, 100);

	this_thread::sleep_for(chrono::seconds(5));
	cout << f5.get();


	return 0;
}