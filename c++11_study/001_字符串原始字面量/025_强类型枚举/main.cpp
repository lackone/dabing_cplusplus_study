#include <iostream>

using namespace std;

// 匿名枚举
//enum { Red, Green, Blue };
// 有名枚举
//enum Colors { Red, Green, Blue };

//C++11标准引入了一种新的枚举类型，即枚举类，又称强类型枚举（strong-typed enum）。
//声明强类型枚举非常简单，只需要在 enum 后加上关键字 class

enum Colors : char { Red, Green, Blue };

//enum class Colors { Red, Green, Blue };

enum class China { Shanghai, Dongjing, Beijing, Nanjing, };

//强类型枚举默认的底层类型为 int，但也可以显式地指定底层类型，具体方法为在枚举名称后面加上∶type，其中 type 可以是除 wchar_t 以外的任何整型。
enum class Japan :char { Dongjing, Daban, Hengbin, Fudao };


int main()
{

	Colors c1 = Green; // C++11以前的用法
	Colors c2 = Colors::Green; // C++11的扩展语法

	return 0;
}