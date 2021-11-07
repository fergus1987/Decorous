#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// 堆排序
class Solution {
public:
	void heapSortAcs(vector<int>& vi) { // 升序
		if (vi.empty())
			return;

		int sz = vi.size();
		for (int i = (sz - 2) / 2; i >= 0; --i) { // 建堆
			maxHeapify(vi, i, sz);
		}

		for (int i = sz - 1; i > 0; --i) {
			std::swap(vi[0], vi[i]);
			maxHeapify(vi, 0, i);
		}
	}

	void heapSortDesc(vector<int>& vi) { // 降序
		if (vi.empty())
			return;

		int sz = vi.size();
		for (int i = (sz - 2) / 2; i >= 0; --i) {
			minHeapify(vi, i, sz);
		}

		for (int i = sz - 1; i > 0; --i) { // 建堆
			std::swap(vi[0], vi[i]);
			minHeapify(vi, 0, i);
		}
	}
private:
	void maxHeapify(vector<int>& vi, int begin, int sz) { // 大顶堆
		int temp = vi[begin], sub = begin * 2 + 1;

		while (sub < sz) {
			if (sub + 1 < sz)
				sub = vi[sub] > vi[sub + 1] ? sub : sub + 1;

			if (vi[sub] > temp) {
				vi[begin] = vi[sub];
				begin = sub;
				sub = sub * 2 + 1;
			}
			else
				break;
		}

		vi[begin] = temp;
	}

	void minHeapify(vector<int>& vi, int begin, int sz) { // 小顶堆
		int temp = vi[begin], sub = begin * 2 + 1;

		while (sub < sz) {
			if (sub + 1 < sz)
				sub = vi[sub] < vi[sub + 1] ? sub : sub + 1;

			if (vi[sub] < temp) {
				vi[begin] = vi[sub];
				begin = sub;
				sub = sub * 2 + 1;
			}
			else
				break;
		}

		vi[begin] = temp;
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	vector<int> vi{ 49,38,65,97,76,13,27,49 };

	sol.heapSortAcs(vi);
	for (int v : vi) {
		cout << v << ' ';
	}
	cout << endl;

	sol.heapSortDesc(vi);
	for (int v : vi) {
		cout << v << ' ';
	}
	cout << endl;

	return 0;
}
