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
			maxHeapify(vi, i, sz); // 升序
			//minHeapify(vi, i, sz); // 降序
		}

		for (int i = sz - 1; i >= 1; --i) {
			std::swap(vi[i], vi[0]);
			maxHeapify(vi, 0, i); // 升序
			//minHeapify(vi, 0, i); // 降序
		}
	}
private:
	void maxHeapify(vector<int>& vi, int parent, int sz) { // 大顶堆
		if (sz == 1) // 针对heapSortAcs函数中第二个for循环 i==1 时
			return;

		int pivot = vi[parent];
		int child = parent * 2 + 1;

		while (child < sz) {
			if (child + 1 < sz)
				child = vi[child + 1] > vi[child] ? child + 1 : child;

			if (vi[child] > pivot) {
				vi[parent] = vi[child];
				parent = child;
				child = child * 2 + 1;
			}
			else
				break;
		}

		vi[parent] = pivot;
	}

	void minHeapify(vector<int>& vi, int parent, int sz) { // 小顶堆
		int pivot = vi[parent];
		int child = parent * 2 + 1;

		while (child < sz) {
			if (child + 1 < sz)
				child = vi[child + 1] < vi[child] ? child +1  : child;

			if (vi[child] < pivot) {
				vi[parent] = vi[child];
				parent = child;
				child = child * 2 + 1;
			}
			else
				break;
		}

		vi[parent] = pivot;
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
