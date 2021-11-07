#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::string;

// 插入排序
class Solution {
public:
	void insertSort(vector<int>& vi) {
		if (vi.empty())
			return;

		for (size_t i = 1; i < vi.size(); ++i) {
			int tmp = vi[i];
			size_t j = i - 1;

			while (j >= 0 && vi[j] > tmp) { // 若 vi[j] > tmp 判断在前，当j自减为-1时vi[-1]将无定义而出错
				vi[j + 1] = vi[j];
				--j;
			}
			vi[++j] = tmp;
		}
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	vector<int> vi{ 49,38,65,97,76,13,27,49 };
	sol.insertSort(vi);
	for (int v : vi) {
		cout << v << ' ';
	}
	cout << endl;

	return 0;
}
