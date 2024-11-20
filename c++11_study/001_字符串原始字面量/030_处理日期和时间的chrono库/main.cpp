#include <iostream>
#include <chrono>

using namespace std;

int main()
{
	chrono::hours h(1);
	chrono::milliseconds ms{ 3 };                // 3 ����
	chrono::duration<int, ratio<1000>> ks(3);    // 3000 ��
	chrono::duration<double> dd(6.6);            // 6.6 ��

	//ʱ������Ϊ1/30�룬����3.5��ʱ�����ڣ�����hz��ʾ��ʱ����Ϊ1/30*3.5��
	chrono::duration<double, std::ratio<1, 30>> hz(3.5);

	chrono::minutes t1(10);
	chrono::seconds t2(60);
	chrono::seconds t3 = t1 - t2;
	cout << t3.count() << " second" << endl;

	//duration�ļӼ�������һ���Ĺ��򣬵�����durationʱ�����ڲ���ͬ��ʱ�򣬻���ͳһ��һ��ʱ�ӣ�Ȼ���ٽ����������㣬
	//ͳһ�Ĺ������£�������ratio<x1,y1> �� ratio<x2,y2>����ʱ�����ڣ�������Ҫ���x1��x2�����Լ��X��Ȼ�����y1��y2����С������Y��ͳһ֮���ʱ������ratioΪratio<X,Y>��
	chrono::duration<double, ratio<9, 7>> d1(3);
	chrono::duration<double, ratio<6, 5>> d2(1);
	// d1 �� d2 ͳһ֮���ʱ������
	chrono::duration<double, ratio<3, 35>> d3 = d1 - d2;


	chrono::system_clock::time_point today = chrono::system_clock::now();

	// ת��Ϊtime_tʱ������
	time_t tm = chrono::system_clock::to_time_t(today);
	char buf[32]{ 0 };
	ctime_s(buf, 32, &tm);
	cout << "�����������:    " << buf;


	// ��ȡ��ʼʱ���
	chrono::steady_clock::time_point start = chrono::steady_clock::now();

	// ��ȡ����ʱ���
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	// �����ֵ
	auto dt = last - start;
	cout << "�ܹ���ʱ: " << dt.count() << "����" << endl;

	return 0;
}