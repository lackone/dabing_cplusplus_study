#include <iostream>
#include <memory>

using namespace std;

//std::weak_ptr没有重载操作符*和->，因为它不共享指针，不能操作资源，所以它的构造不会增加引用计数，
// 析构也不会减少引用计数，它的主要作用就是作为一个旁观者监视shared_ptr中管理的资源是否存在。

//这个问题可以通过weak_ptr来解决，通过wek_ptr返回管理this资源的共享智能指针对象shared_ptr。
//C++11中为我们提供了一个模板类叫做std::enable_shared_from_this<T>，这个类中有一个方法叫做shared_from_this()，
//通过这个方法可以返回一个共享智能指针，在函数的内部就是使用weak_ptr来监测this对象，并通过调用weak_ptr的lock()方法返回一个shared_ptr对象。
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

//解决循环引用问题
struct TA;
struct TB;

struct TA
{
	weak_ptr<TB> bptr; //weak_ptr可以解决这个问题，只要将类TA或者TB的任意一个成员改为weak_ptr
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

	//通过调用std::weak_ptr类提供的expired()方法来判断观测的资源是否已经被释放
	shared_ptr<int> shared(new int(10));
	weak_ptr<int> weak(shared);

	cout << "1. weak " << (weak.expired() ? "is" : "is not") << " expired" << endl;

	shared.reset();
	cout << "2. weak " << (weak.expired() ? "is" : "is not") << " expired" << endl;

	shared_ptr<int> sp1, sp2;
	weak_ptr<int> wp;

	//通过调用std::weak_ptr类提供的lock()方法来获取管理所监测资源的shared_ptr对象
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

	//通过调用std::weak_ptr类提供的reset()方法来清空对象，使其不监测任何资源

	shared_ptr<int> sp33(new int(10));
	weak_ptr<int> wp33(sp33);
	cout << "1. wp " << (wp33.expired() ? "is" : "is not") << " expired" << endl;
	wp33.reset();
	cout << "2. wp " << (wp33.expired() ? "is" : "is not") << " expired" << endl;

	//返回管理this的shared_ptr
	shared_ptr<Test> sp11(new Test);
	cout << "use_count: " << sp11.use_count() << endl;
	shared_ptr<Test> sp22 = sp11->getSharedPtr();
	cout << "use_count: " << sp11.use_count() << endl;

	//智能指针如果循环引用会导致内存泄露
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