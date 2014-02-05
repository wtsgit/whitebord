/*
http://oj.leetcode.com/problems/add-two-numbers/
Wed Dec 18 19:35:42 EST 2013


Add Two Numbers

You are given two linked lists representing two non-negative numbers.
The digits are stored in reverse order and each of their nodes
contain a single digit. Add the two numbers and return it as a
linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

#include <iostream>
#include <list>
#include <iterator>
#include "leet.h"

template<typename IT_R, typename IT>
void addTwoNumbers(IT_R r, IT p, IT p_end, IT q, IT q_end) {
	if (p == p_end) {
		std::swap(p, q);
		std::swap(p_end, q_end);
	}

	int carry = 0;
	while (p != p_end) {
		int n = *p + carry;
		++p;
		if (q != q_end) {
			n += *q;
			++q;
		}
		if (p == p_end) {
			std::swap(p, q);
			std::swap(p_end, q_end);
		}
		carry = (n >= 10) ? 1 : 0;
		n -= (n >= 10) ? 10 : 0;
		*r = n;
		++r;
	}
	if (carry == 1) {
		*r = 1;
		++r;
	}
}

template<typename C>
C& addTwoNumbers(C &r, const C &c1, const C &c2) {
	addTwoNumbers(std::back_inserter(r), c1.begin(), c1.end(), c2.begin(), c2.end());
	return r;
}

class SolutionOld {
public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		if (l1 == 0) {
			std::swap(l1, l2);
		}

		ListNode *r0 = new ListNode(0);
		ListNode *r = r0;
		int carry = 0;
		while (l1 != 0) {
			int n = l1->val + carry;
			l1 = l1->next;
			if (l2 != 0) {
				n += l2->val;
				l2 = l2->next;
			}
			if (l1 == 0) {
				std::swap(l1, l2);
			}
			carry = (n >= 10) ? 1 : 0;
			n -= (n >= 10) ? 10 : 0;
			r->next = new ListNode(n);
			r = r->next;
		}
		if (carry == 1) {
			r->next = new ListNode(1);
			r = r->next;
		}
		r = r0->next;
		delete r0;
		return r;
	}
};


class Solution {
public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		ListNode dummy(0);
		auto l3 = &dummy;
		int carry = 0;
		while (l1 && l2) {
			l3->next = new ListNode(l1->val + l2->val + carry);
			carry = 0;
			l3 = l3->next;
			if (l3->val >= 10) {
				l3->val -= 10;
				carry = 1;
			}
			l1 = l1->next;
			l2 = l2->next;
		}
		l1 = l1 ? l1 : l2;
		while (l1) {
			l3->next = new ListNode(l1->val + carry);
			carry = 0;
			l3 = l3->next;
			if (l3->val >= 10) {
				l3->val -= 10;
				carry = 1;
			}
			l1 = l1->next;
		}
		if (carry) {
			l3->next = new ListNode(carry);
		}
		return dummy.next;
	}
};


int main()
{
	std::list<int> l1{1, 2, 3};
	std::list<int> l2{5, 6, 4};
	std::list<int> l3;

	addTwoNumbers(l3, l1, l2);
	std::copy(l3.begin(), l3.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	return 0;
}
