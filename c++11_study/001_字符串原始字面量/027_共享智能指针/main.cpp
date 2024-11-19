#include <iostream>
#include <memory>

using namespace std;

//C++11���ṩ����������ָ�룬ʹ����Щ����ָ��ʱ��Ҫ����ͷ�ļ�<memory>��

//std::shared_ptr�����������ָ��
//std::unique_ptr����ռ������ָ��
//std::weak_ptr�������õ�����ָ�룬��������ָ�룬���ܲ�����Դ������������shared_ptr�ġ�

//��������ָ����ָ�������ָ�����ͬʱ����ͬһ����Ч���ڴ�

class Test
{
public:
	Test()
	{
		cout << "construct Test..." << endl;
	}
	Test(int x)
	{
		cout << "construct Test, x = " << x << endl;
	}
	Test(string str)
	{
		cout << "construct Test, str = " << str << endl;
	}
	~Test()
	{
		cout << "destruct Test ..." << endl;
	}
};

void delPtr(int* p)
{
	delete p;
	cout << "int ���ڴ汻�ͷ���..." << endl;
}

int main()
{
	//ͨ�����캯����ʼ��
	shared_ptr<int> p1(new int(100));
	cout << p1.use_count() << endl; //���ü���

	shared_ptr<char> p2(new char[10]);
	cout << p2.use_count() << endl;

	shared_ptr<int> p3;
	cout << p3.use_count() << endl;

	shared_ptr<int> p4(nullptr);
	cout << p4.use_count() << endl;

	//��Ҫʹ��һ��ԭʼָ���ʼ�����shared_ptr��
	//int* pp = new int;
	//shared_ptr<int> pp1(pp);
	//shared_ptr<int> pp2(pp);

	//ͨ���������ƶ����캯����ʼ��
	shared_ptr<int> p5(new int(300));
	cout << p5.use_count() << endl;
	shared_ptr<int> p6(p5);
	cout << p6.use_count() << endl;
	shared_ptr<int> p7 = p5;
	cout << p7.use_count() << endl;
	shared_ptr<int> p8(std::move(p5));
	cout << p8.use_count() << endl;
	std::shared_ptr<int> p9 = std::move(p6);
	cout << p9.use_count() << endl;

	//ͨ��std::make_shared��ʼ��
	shared_ptr<int> ptr1 = make_shared<int>(520);
	shared_ptr<Test> ptr2 = make_shared<Test>();
	shared_ptr<Test> ptr3 = make_shared<Test>(520);
	shared_ptr<Test> ptr4 = make_shared<Test>("test");

	//ͨ�� reset ������ʼ��

	shared_ptr<int> ptr5;
	ptr5.reset(new int(250));
	cout << ptr5.use_count() << endl;

	//��ȡԭʼָ��
	shared_ptr<char> pstr(new char[32]);
	char* str = pstr.get();
	memset(str, 0, 32);
	strcpy_s(str, 32, "test");
	cout << str << endl;

	//ָ��ɾ����
	shared_ptr<int> ptr(new int(250), delPtr);

	return 0;
}