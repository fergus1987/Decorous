#include <iostream>

using std::cout;
using std::endl;

class Solution {
public:
	void printNumbers(int n) {
		if (n <= 0)
			return;

		char* pNum = new char[n + 1];
		for (int i = 0; i < 10; ++i) {
			pNum[0] = i + '0';
			recursion(pNum, n, 0);
		}

		delete[] pNum;
	}
private:
	void recursion(char* pNum, int n, int pos) {
		if (pos == n - 1) {
			printNum(pNum, n);
			return;
		}

		for (int i = 0; i < 10; ++i) {
			pNum[pos + 1] = i + '0';
			recursion(pNum, n, pos + 1);
		}
	}

	void printNum(char* pNum, int n) {
		int i = 0;
		while (pNum[i++] == '0') {
			if (i == n) {
				cout << '0' << endl;
				return;
			}
			else
				continue;
		}

		for (int j = --i; j < n; ++j) {
			cout << pNum[j];
		}
		cout << endl;
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	sol.printNumbers(3);

	return 0;
}