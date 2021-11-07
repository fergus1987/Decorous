#include <iostream>

using std::cout;
using std::endl;

// 二级指针的应用
class Solution {
public:
	bool isNumeric(const char* str) {
		if (str == nullptr)
			return false;

		bool rst = scanSigned(&str);

		if (*str == '.') {
			++str;
			rst = scanUnsigned(&str) || rst; // 逻辑或运算“A||B”→ 若A为真则不会再计算B的值而直接返回真
							// “或运算”针对情况".22"，变量顺序为“当rst为真时指针str可继续前移”
		}
		if (*str == 'e' || *str == 'E') {
			++str;
			rst = rst && scanSigned(&str);
		}

		return rst && *str == '\0'; // *str == '\0'判断 针对情况“2.2.2”和“2e2.2”
	}
private:
	bool scanSigned(const char** str) {
		if (**str == '+' || **str == '-')
			++(*str);
		return scanUnsigned(str);
	}

	bool scanUnsigned(const char** str) {
		const char* temp = *str;
		while (**str != '\0' && **str >= '0' && **str <= '9') {
			++(*str);
		}
		return *str > temp;
	}
};

int main(int argc, char* argv[]) {
	Solution sol;

	cout << sol.isNumeric("+100") << endl;
	cout << sol.isNumeric("5e2") << endl;
	cout << sol.isNumeric("-123") << endl;
	cout << sol.isNumeric("3.14") << endl;
	cout << sol.isNumeric("-1E-16") << endl;
	cout << sol.isNumeric(".14") << endl;
	cout << sol.isNumeric("0.14e+123") << endl;
	cout << sol.isNumeric("2.") << endl;
	cout << endl;
	cout << sol.isNumeric(nullptr) << endl;
	cout << sol.isNumeric("12e") << endl;
	cout << sol.isNumeric("1a3.14") << endl;
	cout << sol.isNumeric("1.2.3") << endl;
	cout << sol.isNumeric("+-5") << endl;
	cout << sol.isNumeric("12e+5.4") << endl;

	return 0;
}
