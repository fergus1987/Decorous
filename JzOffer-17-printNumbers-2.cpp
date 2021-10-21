#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;

class Solution {
public:
	vector<int> printNumbers(int n) {
		if (n <= 0)
			return vector<int>();

		recursion(n, 0);

		return rst;
	}
private:
	vector<int> rst;
	string stNum;

	void recursion(int n, int pos) {
		if (pos == n) {
			pushBack();
			return;
		}

		for (int i = 0; i <= 9; ++i) {
			stNum[pos] = i + '0';
			recursion(n, pos + 1);
		}
	}

	void pushBack() {
		int temp = std::stoi(stNum);
		if (temp != 0)
			rst.push_back(temp));
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	vector<int> v = sol.printNumbers(3);
	for (int i : v) {
		cout << i << endl;
	}

	return 0;
}