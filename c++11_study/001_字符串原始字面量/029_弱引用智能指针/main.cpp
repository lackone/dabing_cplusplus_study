#include <iostream>
#include <memory>

using namespace std;

//std::weak_ptrû�����ز�����*��->����Ϊ��������ָ�룬���ܲ�����Դ���������Ĺ��첻���������ü�����
// ����Ҳ����������ü�����������Ҫ���þ�����Ϊһ���Թ��߼���shared_ptr�й������Դ�Ƿ���ڡ�

//����������ͨ��weak_ptr�������ͨ��wek_ptr���ع���this��Դ�Ĺ�������ָ�����shared_ptr��
//C++11��Ϊ�����ṩ��һ��ģ�������std::enable_shared_from_this<T>�����������һ����������shared_from_this()��
//ͨ������������Է���һ����������ָ�룬�ں������ڲ�����ʹ��weak_ptr�����this���󣬲�ͨ������weak_ptr��lock()��������һ��shared_ptr����
struct Test : public enable_shared_from_this<Test>
{
	shared_ptr<Test> getSharedPtr()
	{
		return shared_from_this();
	}
	~Test()
	{
		cout << "class Test is distruct ..." << endl;
	}
};

//���ѭ����������
struct TA;
struct TB;

struct TA
{
	weak_ptr<TB> bptr; //weak_ptr���Խ��������⣬ֻҪ����TA����TB������һ����Ա��Ϊweak_ptr
	~TA()
	{
		cout << "class TA is distruct ..." << endl;
	}
};

struct TB
{
	shared_ptr<TA> aptr;
	~TB()
	{
		cout << "class TB is distruct ..." << endl;
	}
};

int main()
{
	shared_ptr<int> sp(new int);

	weak_ptr<int> wp1;
	weak_ptr<int> wp2(wp1);
	weak_ptr<int> wp3(sp);
	weak_ptr<int> wp4;
	wp4 = sp;
	weak_ptr<int> wp5;
	wp5 = wp3;

	cout << "use_count: " << endl;
	cout << "wp1: " << wp1.use_count() << endl;
	cout << "wp2: " << wp2.use_count() << endl;
	cout << "wp3: " << wp3.use_count() << endl;
	cout << "wp4: " << wp4.use_count() << endl;
	cout << "wp5: " << wp5.use_count() << endl;

	//ͨ������std::weak_ptr���ṩ��expired()�������жϹ۲����Դ�Ƿ��Ѿ����ͷ�
	shared_ptr<int> shared(new int(10));
	weak_ptr<int> weak(shared);

	cout << "1. weak " << (weak.expired() ? "is" : "is not") << " expired" << endl;

	shared.reset();
	cout << "2. weak " << (weak.expired() ? "is" : "is not") << " expired" << endl;

	shared_ptr<int> sp1, sp2;
	weak_ptr<int> wp;

	//ͨ������std::weak_ptr���ṩ��lock()��������ȡ�����������Դ��shared_ptr����
	sp1 = std::make_shared<int>(520);
	wp = sp1;
	sp2 = wp.lock();
	cout << "use_count: " << wp.use_count() << endl;

	sp1.reset();
	cout << "use_count: " << wp.use_count() << endl;

	sp1 = wp.lock();
	cout << "use_count: " << wp.use_count() << endl;

	cout << "*sp1: " << *sp1 << endl;
	cout << "*sp2: " << *sp2 << endl;

	//ͨ������std::weak_ptr���ṩ��reset()��������ն���ʹ�䲻����κ���Դ

	shared_ptr<int> sp33(new int(10));
	weak_ptr<int> wp33(sp33);
	cout << "1. wp " << (wp33.expired() ? "is" : "is not") << " expired" << endl;
	wp33.reset();
	cout << "2. wp " << (wp33.expired() ? "is" : "is not") << " expired" << endl;

	//���ع���this��shared_ptr
	shared_ptr<Test> sp11(new Test);
	cout << "use_count: " << sp11.use_count() << endl;
	shared_ptr<Test> sp22 = sp11->getSharedPtr();
	cout << "use_count: " << sp11.use_count() << endl;

	//����ָ�����ѭ�����ûᵼ���ڴ�й¶
	shared_ptr<TA> ap(new TA);
	shared_ptr<TB> bp(new TB);
	cout << "TA object use_count: " << ap.use_count() << endl;
	cout << "TB object use_count: " << bp.use_count() << endl;

	ap->bptr = bp;
	bp->aptr = ap;
	cout << "TA object use_count: " << ap.use_count() << endl;
	cout << "TB object use_count: " << bp.use_count() << endl;

	return 0;
}