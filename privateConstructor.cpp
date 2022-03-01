#include <iostream>
using namespace std;

// 私有构造函数类
class prvtCnstr {
public: // 利用静态公有成员函数创建对象
	static prvtCnstr* getObject_default() { return new prvtCnstr; }
	static prvtCnstr* getObject_Prtr() { return new prvtCnstr(1); }
	static prvtCnstr getObject() {
		prvtCnstr s(2);
		return s;
	}

	int getVal() { return val; }

	void destroy() {
		delete this;
		cout << "The Object has been deleted." << endl;
	}
private:
	int val;
	prvtCnstr() :val(0) {} // 私有默认构造函数
	prvtCnstr(int i) :val(i) {} // 私有重载构造函数
};

int main(int argc, char* argv[]) {
	prvtCnstr* ptr1 = prvtCnstr::getObject_default();
	prvtCnstr* ptr2 = prvtCnstr::getObject_Prtr();
	prvtCnstr pC = prvtCnstr::getObject();
	cout << ptr1->getVal() << endl;
	cout << ptr2->getVal() << endl;
	cout << pC.getVal() << endl;

	// 两种释放动态内存的方式
	ptr1->destroy();
	delete ptr2;

	return 0;
}