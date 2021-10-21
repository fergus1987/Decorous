#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using std::vector;
using std::cout;
using std::endl;
using std::string;

class Solution {
public:
	void sort(vector<int>& nums) {
		if (nums.empty())
			return;

		quickSort(nums, 0, nums.size() - 1);
	}
private:
	void quickSort(vector<int>& nums, int lf, int rt) {
		if (lf >= rt)
			return;

		int min = lf, max = rt;

		srand(time(0));
		int randomIndex = rand() % (rt - lf + 1) + lf;
		std::swap(nums[randomIndex], nums[rt]);

		int pivot = nums[lf];
		while (lf < rt) {
			while (lf < rt && nums[rt] >= pivot)
				--rt;
			nums[lf] = nums[rt];
			while (lf < rt && nums[lf] <= pivot)
				++lf;
			nums[rt] = nums[lf];
		}
		nums[lf] = pivot;

		quickSort(nums, min, lf - 1);
		quickSort(nums, lf + 1, max);
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	vector<int> vi{ 5,4,3,2,1 };
	sol.sort(vi);
	for (int v : vi) {
		cout << v << ' ';
	}
	cout << endl;

	return 0;
}