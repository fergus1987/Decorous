#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// 数组两元素地址相减 → 获取两元素的数组距离而非地址距离
int main(int argc, char* argv[]) {
	//以下两种写法结果一致
	string* st = new string[2]{ "Tang","Cong" };
	//string st[2]{ "Tang","Cong" };

	string* p1 = st + 0, *p2 = st + 1;
	// 若写为 string* p1 = st，p1类型 * string []，而p2类型 * string，不能进行随后的减法操作

	cout << *p1 << endl; // 打印 Tang
	cout << *p2 << endl; // 打印 Cong
	cout << p1 << endl; // 打印 16进制内存地址，同 cout << st << endl;
	cout << p2 << endl; // 打印 上述内存地址 + 4字节，同 cout << st + 1 << endl;

	cout << p2 - p1 << endl; // 打印1（数组距离），同 &st[1] - &st[0]
	cout << (void*)p2 - (void*)p1 << endl; // 打印俩元素地址距离，同 (void*)&st[1] - (void*)&st[0]

	return 0;
}
