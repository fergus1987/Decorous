#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;

// 回溯
class Solution {
public:
	vector<int> printNumbers(int n) {
		if (n == 0)
			return rst;

		backtrack(n, 1);
		return rst;
	}
private:
	vector<int> rst;
	string stNum;

	void backtrack(int n, int pos) {
		if (pos > n) {
			if (stoi(stNum) != 0)
				rst.push_back(stoi(stNum));
			return;
		}

		for (int i = 0; i <= 9; ++i) {
			stNum.push_back(i + '0');
			backtrack(n, pos + 1);
			stNum.pop_back();
		}
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	vector<int> vi = sol.printNumbers(3);
	for (int v : vi) {
		cout << v << endl;
	}

	return 0;
}
