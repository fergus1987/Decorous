#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// basic_string::c_str()的应用
int main(int argc, char* argv[]) {
	Solution sol;

	string s = "tang";
	char ch[10];
	// c_str()返回const char*，故不能用char*接收
	const char* conCh = s.c_str();
	strcpy(ch, s.c_str());

	cout << &s << endl;
	// 强转为字符串首地址，否则将打印以该地址为起始的字符串
	cout << (void*)conCh << endl; // 指向s的首地址
	cout << (int*)ch << endl;

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
