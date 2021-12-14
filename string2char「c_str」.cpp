#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// basic_string::c_str()的应用
int main(int argc, char* argv[]) {
	string s = "tang";
	char ch[10];
	const char* conCh = s.c_str(); // 注意 c_str() 返回 const char*
	strcpy(ch, s.c_str()); // strcpy() 参2 也为 const char*

	cout << &s << endl;

	// 强转为字符串首地址，否则将打印以该地址为起始的字符串
	cout << (void*)conCh << endl; // 指向s首地址
	cout << (int*)ch << endl; // 指向ch首地址

	s[1] = 'o';
	cout << s << endl;
	cout << conCh << endl; // 结果与s一样被改变
	cout << ch << endl;

	return 0;
}

/*
 * 输出：
 * 00000090B557FC78
 * 00000090B557FC78
 * 00000090B557FC98
 * tong
 * tong
 * tang
*/
