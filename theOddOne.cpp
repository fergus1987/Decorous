#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*
 * 找到一组数中唯一一个出现奇数次的数
 * 
 * 利用「异或运算」：
 * a^a = 0   a^0 = a   a^b = b^a   a^b^c = a^(b^c)
 * a^b^a = b^a^a = b^0 = b
 */
int main(int argc, char* argv[]) {
	vector<int> vi{ 1,2,3,1,2,3,1 };
	int rst = 0;

	for (int v : vi) {
		rst ^= v;
	}

	cout << rst << endl;

	return 0;
}
