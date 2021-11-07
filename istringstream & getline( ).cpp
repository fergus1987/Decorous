#include <iostream>
#include <sstream> // for istringstream
#include <vector>
#include <string>
#include <algorithm> // for sort

using namespace std;

/*
 * istringstream 与 getline(3个参数) 的应用
 *
 * 循环输入字符串，分别进行排序
 * 以输入字符串 "a,cc,cb,b" 为例，程序将输出 "a,b,cb,cc"
 */
int main(int argc, char* argv[]) {
	vector<string> vs;
	string tmp;

	while (cin >> tmp) { // tmp 将保存 "a,cc,cb,b" 整个字符串
		istringstream iss(tmp); // istringstream 输入流对象使用 string 初始化
		while (getline(iss, tmp, ',')) { // 将 iss 输入流对象中的字符读入 tmp 直到遇到定界字符 ',' 或读取到最大长度
			vs.emplace_back(tmp);        // 这里分别将 "a"、"cc"、"cb"、"b" 存入 vs
		}
		sort(vs.begin(), vs.end());
		for (int i = 0; i < vs.size(); ++i) {
			if (i != vs.size() - 1)
				cout << vs[i] << ',';
			else
				cout << vs[i] << endl;
		}
		vs.clear(); // 清空容器准备下一次接收
	}

	return 0;
}
