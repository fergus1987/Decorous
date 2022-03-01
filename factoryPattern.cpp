#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Factory Pattern
class operation { // 抽象基类（ABC）
public:
	virtual double getResult() = 0; // 纯虚函数

	void setOper1(double data) {
		operand1 = data;
	}
	void setOper2(double data) {
		operand2 = data;
	}
protected:
	double getOper1() const { // 对私有成员的只读访问
		return operand1;
	}
	double getOper2() const { // 对私有成员的只读访问
		return operand2;
	}
private:
	double operand1 = 0, operand2 = 0;
};

// 公有派生
class operationAdd : public operation {
public:
	virtual double getResult() {
		return getOper1() + getOper2();
	}
};
class operationSub : public operation {
public:
	double getResult() {
		return getOper1() - getOper2();
	}
};
class operationMul : public operation {
public:
	double getResult() {
		return getOper1() * getOper2();
	}
};
class operationDiv : public operation {
public:
	double getResult() {
		if (getOper2() == 0) {
			cout << "operand2 cannot be ZERO!" << endl;
			exit(1);
		}
		return getOper1() / getOper2();
	}
};

// 派生类工厂
class operationFactory {
public:
	static operation* createOperation(const char op) { //静态方法
		operation* oper = nullptr;

		switch (op) {
		case '+': oper = new operationAdd; break;
		case '-': oper = new operationSub; break;
		case '*': oper = new operationMul; break;
		case '/': oper = new operationDiv;
		}

		return oper;
	}
};

int main(int argc, char* argv[]) {

	operation* oper = operationFactory::createOperation('+');
	oper->setOper1(4);
	oper->setOper2(5);
	cout << oper->getResult() << endl;

	return 0;
}
