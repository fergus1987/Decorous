#include <iostream>
using namespace std;

// ˽�й��캯��
class prvtCnstr {
private:
	int val;
	prvtCnstr() :val(0) {} // Ĭ�Ϲ��캯��
	prvtCnstr(int i) :val(i) {} // ���ع��캯��
public:
	static prvtCnstr* getObject_default() { return new prvtCnstr; }
	static prvtCnstr* getObject_Prtr() { return new prvtCnstr(1); }
	static prvtCnstr getObject() {
		prvtCnstr s(2); // ���ڲ��ſɴ�������
		return s;
	}

	int getVal() { return val; }

	void destroy() {
		delete this;
		cout << "the Object has deleted." << endl;
	}
};

int main(int argc, char* argv[]) {
	// �������캯��Ϊ˽��ʱ�������
	prvtCnstr* ptr1 = prvtCnstr::getObject_default();
	prvtCnstr* ptr2 = prvtCnstr::getObject_Prtr();
	prvtCnstr pC = prvtCnstr::getObject();
	cout << ptr1->getVal() << endl;
	cout << ptr2->getVal() << endl;
	cout << pC.getVal() << endl;

	// �����ͷŶ�̬�ڴ�ķ�ʽ
	ptr1->destroy();
	ptr2->destroy();
	//delete ptr1;
	//delete ptr2;

	return 0;
}