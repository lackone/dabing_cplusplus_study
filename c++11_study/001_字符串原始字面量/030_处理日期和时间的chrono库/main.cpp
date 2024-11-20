#include <iostream>
#include <chrono>

using namespace std;

int main()
{
	chrono::hours h(1);
	chrono::milliseconds ms{ 3 };                // 3 毫秒
	chrono::duration<int, ratio<1000>> ks(3);    // 3000 秒
	chrono::duration<double> dd(6.6);            // 6.6 秒

	//时钟周期为1/30秒，共有3.5个时钟周期，所以hz表示的时间间隔为1/30*3.5秒
	chrono::duration<double, std::ratio<1, 30>> hz(3.5);

	chrono::minutes t1(10);
	chrono::seconds t2(60);
	chrono::seconds t3 = t1 - t2;
	cout << t3.count() << " second" << endl;

	//duration的加减运算有一定的规则，当两个duration时钟周期不相同的时候，会先统一成一种时钟，然后再进行算术运算，
	//统一的规则如下：假设有ratio<x1,y1> 和 ratio<x2,y2>两个时钟周期，首先需要求出x1，x2的最大公约数X，然后求出y1，y2的最小公倍数Y，统一之后的时钟周期ratio为ratio<X,Y>。
	chrono::duration<double, ratio<9, 7>> d1(3);
	chrono::duration<double, ratio<6, 5>> d2(1);
	// d1 和 d2 统一之后的时钟周期
	chrono::duration<double, ratio<3, 35>> d3 = d1 - d2;


	chrono::system_clock::time_point today = chrono::system_clock::now();

	// 转换为time_t时间类型
	time_t tm = chrono::system_clock::to_time_t(today);
	char buf[32]{ 0 };
	ctime_s(buf, 32, &tm);
	cout << "今天的日期是:    " << buf;


	// 获取开始时间点
	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	// 获取结束时间点
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	// 计算差值
	auto dt = last - start;
	cout << "总共耗时: " << dt.count() << "纳秒" << endl;

	return 0;
}