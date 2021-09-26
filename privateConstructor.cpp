#include <iostream>
using namespace std;

// 私有构造函数
class prvtCnstr {
private:
	int val;
	prvtCnstr() :val(0) {} // 默认构造函数
	prvtCnstr(int i) :val(i) {} // 重载构造函数
public:
	static prvtCnstr* getObject_default() { return new prvtCnstr; }
	static prvtCnstr* getObject_Prtr() { return new prvtCnstr(1); }
	static prvtCnstr getObject() {
		prvtCnstr s(2); // 类内部才可创建对象
		return s;
	}

	int getVal() { return val; }

	void destroy() {
		delete this;
		cout << "the Object has deleted." << endl;
	}
};

int main(int argc, char* argv[]) {
	// 创建构造函数为私有时的类对象
	prvtCnstr* ptr1 = prvtCnstr::getObject_default();
	prvtCnstr* ptr2 = prvtCnstr::getObject_Prtr();
	prvtCnstr pC = prvtCnstr::getObject();
	cout << ptr1->getVal() << endl;
	cout << ptr2->getVal() << endl;
	cout << pC.getVal() << endl;

	// 两种释放动态内存的方式
	ptr1->destroy();
	ptr2->destroy();
	//delete ptr1;
	//delete ptr2;

	return 0;
}