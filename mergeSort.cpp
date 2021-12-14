#include <iostream>

using std::cout;
using std::endl;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() :val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 归并排序实现的两种实现
class Solution {
public:
	// 自顶向下
	ListNode* mergeSort(ListNode* head) {
		if (!head)
			return nullptr;

		return recursion(head, nullptr);
	}

	ListNode* recursion(ListNode* head, ListNode* tail) {
		if (head->next == tail) {
			head->next = nullptr;
			return head;
		}

		ListNode* slow = head, * fast = head;
		while (fast != tail) {
			slow = slow->next;
			fast = fast->next;
			if (fast != tail)
				fast = fast->next;
		}

		/*ListNode* mid = slow;
		ListNode* head1 = recursion(head, mid), * head2 = recursion(mid, tail);*/

		ListNode* head1 = recursion(head, slow), * head2 = recursion(slow, tail);
		return merge(head1, head2);
	}

	// 自底向上
	ListNode* mergeSort(ListNode* head) {
		if (!head)
			return nullptr;

		int Lnth = 0;
		ListNode* tmp = head;
		while (tmp) {
			++Lnth;
			tmp = tmp->next;
		}

		// 若使用 ListNode* dummyHead = new ListNode(0, head) 初始化，该内存空间将不会delete，造成内存泄漏
		ListNode dummyHead(0, head);
		for (int subLnth = 1; subLnth < Lnth; subLnth <<= 1) {
			ListNode* pre = &dummyHead, * curr = dummyHead.next;
			while (curr) {
				ListNode* head1 = curr;
				for (int i = 1; i < subLnth && curr->next; ++i) {
					curr = curr->next;
				}
				ListNode* head2 = curr->next;
				curr->next = nullptr;

				curr = head2;
				for (int i = 1; i < subLnth && curr && curr->next; ++i) {
					curr = curr->next;
				}
				if (curr) { // 长度为奇数时，当head1指向最后结点，curr与head2为nullptr
					ListNode* next = curr->next;
					curr->next = nullptr;
					curr = next;
				}

				pre->next = merge(head1, head2);
				while (pre->next) {
					pre = pre->next;
				}
			}
		}

		return dummyHead.next;
	}
private:
	ListNode* merge(ListNode* head1, ListNode* head2) {
		ListNode dummyHead, * tmp = &dummyHead;
		while (head1 && head2) {
			if (head1->val < head2->val) {
				tmp->next = head1;
				head1 = head1->next;
			}
			else {
				tmp->next = head2;
				head2 = head2->next;
			}
			tmp = tmp->next;
		}
		/*if (head1)
			tmp->next = head1;
		else if (head2)
			tmp->next = head2;*/
		tmp->next = head1 != nullptr ? head1 : head2;

		return dummyHead.next;
	}
};

int main(int argc, char* argv[]) {
	Solution sol;



	return 0;
}
