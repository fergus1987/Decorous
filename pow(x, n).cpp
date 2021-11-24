#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// pow(x, n) 时间复杂度 log(n) 的实现
class Solution {
public:
	double myPow(double x, int n) {
		if (x == 0 && n < 0) { // 分母为0的情况
			perror("bad input");
			exit(1);
		}
		else if (n == 0)
			return 1;

		// 为避免n为最大负值（4字节：0x80000000）并取反时的溢出，即将 -2147483648 转换为 2147483648
		long long temp = n;
		unsigned int exponent = n < 0 ? (unsigned int)(-temp) : (unsigned int)temp;

		double rstWithoutSign = recursion(x, exponent);
		double rst = n < 0 ? 1.0 / rstWithoutSign : rstWithoutSign;

		return rst;
	}
private:
	/*
	 * 递归计算a^n:
	 * n为偶：a^n = a^(n/2)*a^(n/2)
	 * n为奇：a^n = a^((n-1)/2)*a^((n-1)/2)*a
	 */
	double recursion(double base, unsigned int exp) {
		if (exp == 1)
			return base;

		double temp = recursion(base, exp >> 1);
		// 判断exp的奇偶
		double rst = (exp & 0x1) == 1 ? temp * temp * base : temp * temp;

		return rst;
	}
};

int main(int argc, char* argv[]) {
	Solution sol;



	return 0;
}
