#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// 用位运算实现整数加法（算法对正、负、零通用）
class Solution {
public:
	int getSum(int a, int b) {
		/*
		 * 赋给signed类型一个超出其范围的值时将溢出，而unsigned类型不会
		 * 赋给unsigned类型一个超出其范围值时，结果 = 所赋值 % 该unsigned类型所能表示的数值数
		 * 例：unsigned int a 为 3 bit，赋值 a = (unsigned int)11
		 * 因a能表示2^3=8个数值，故最终 a = 11 % 8 = 3
		 * 从二进制来看：11 → 1011，3 → 011，即直接去掉超出的位数
		 */
		unsigned int A = a, B = b, carry = 0;

		do {
			carry = (A & B) << 1; // 进位，与运算、左移运算
			A = A ^ B; // 无进位加法，异或运算
			B = carry;
		} while (B);

		return A;
	}
private:

};

int main(int argc, char* argv[]) {
	Solution sol;



	return 0;
}
