#include <iostream>
#include <memory>

using namespace std;

int main()
{
	unique_ptr<int> ptr1(new int(10));

	//������һ��unique_ptr��ֵ����һ��unique_ptr
	//unique_ptr<int> ptr2 = ptr1;

	// ͨ��ת������Ȩ�ķ�ʽ��ʼ��
	unique_ptr<int> ptr2 = move(ptr1);

	//ptr1.reset();�����ԭʼ�ڴ�Ĺ���
	//ptr2.reset(new int(250)); ����ָ������ָ������ԭʼ�ڴ�

	ptr1.reset();
	ptr2.reset(new int(250));

	//��ȡ��ռ����ָ������ԭʼ��ַ
	cout << *ptr2.get() << endl;

	//unique_ptrָ��ɾ������shared_ptrָ��ɾ������������ģ�unique_ptrָ��ɾ������ʱ����Ҫȷ��ɾ���������ͣ����Բ�����shared_ptr����ֱ��ָ��ɾ����

	using func_ptr = void(*)(int*);
	unique_ptr<int, func_ptr> ptr3(new int(10), [](int* p) {delete p; });

	return 0;
}