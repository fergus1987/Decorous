#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// 冒泡排序
class Solution {
public:
	void bubbleSort(vector<int>& vi) {
		if (vi.empty())
			return;

		for (size_t i = vi.size() - 1; i >= 1; --i) {
			int flg = 1;

			for (size_t j = 1; j <= i; ++j) {
				if (vi[j - 1] > vi[j]) {
					std::swap(vi[j - 1], vi[j]);
					flg = 0; // 此轮若进行了排序，置0
				}
			}

			if (flg) // 此轮若未进行排序，说明数列已有序，排序提前结束
				return;
		}
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	vector<int> vi{ 49,38,65,97,76,13,27,49 };
	sol.bubbleSort(vi);
	for (int v : vi) {
		cout << v << ' ';
	}
	cout << endl;

	return 0;
}
