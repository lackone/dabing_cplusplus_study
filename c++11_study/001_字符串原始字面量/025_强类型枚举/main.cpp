#include <iostream>

using namespace std;

// ����ö��
//enum { Red, Green, Blue };
// ����ö��
//enum Colors { Red, Green, Blue };

//C++11��׼������һ���µ�ö�����ͣ���ö���࣬�ֳ�ǿ����ö�٣�strong-typed enum����
//����ǿ����ö�ٷǳ��򵥣�ֻ��Ҫ�� enum ����Ϲؼ��� class

enum Colors : char { Red, Green, Blue };

//enum class Colors { Red, Green, Blue };

enum class China { Shanghai, Dongjing, Beijing, Nanjing, };

//ǿ����ö��Ĭ�ϵĵײ�����Ϊ int����Ҳ������ʽ��ָ���ײ����ͣ����巽��Ϊ��ö�����ƺ�����ϡ�type������ type �����ǳ� wchar_t ������κ����͡�
enum class Japan :char { Dongjing, Daban, Hengbin, Fudao };


int main()
{

	Colors c1 = Green; // C++11��ǰ���÷�
	Colors c2 = Colors::Green; // C++11����չ�﷨

	return 0;
}