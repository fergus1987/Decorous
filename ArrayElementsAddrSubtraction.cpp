#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// 同数组两元素地址相减的测试
int main(int argc, char* argv[]) {

	//以下两种写法结果一致
	string* st = new string[2]{ "Tang","Cong" };
	//string st[2]{ "Tang","Cong" };

	/* 若写成 p1 = st 将无法成功编译 原因分析：
	 * p1 = st 时 p1 是 string[] 指针 而 p2 是 string 指针 故两者不能直接进行加减运算
	 */
	string* p1 = st + 0, *p2 = st + 1;

	cout << *p1 << endl; // 打印 Tang
	cout << *p2 << endl; // 打印 Cong
	cout << p1 << endl; // 打印 16进制内存地址 同 cout << st << endl;
	cout << p2 << endl; // 打印 上述内存地址 + 4字节 同 cout << st + 1 << endl;
	cout << p2 - p1 << endl; // 打印 1
	cout << &st[1] - &st[0] << endl; // 打印 1

	return 0;
}
