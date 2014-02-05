/*
http://oj.leetcode.com/problems/insertion-sort-list/
Wed Jan  1 23:43:57 EST 2014


Insertion Sort List

Sort a linked list using insertion sort.
*/

#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	void insert(ListNode **_head, ListNode **_tail, ListNode *p) {
		ListNode *head = *_head;
		ListNode *tail = *_tail;
		if (p->val < head->val) {
			p->next = head;
			head = p;
		}
		else if (p->val >= tail->val) {
			tail->next = p;
			tail = p;
		}
		else {
			ListNode *curp = head;
			while (curp->next && p->val >= curp->next->val) {
				curp = curp->next;
			}
			p->next = curp->next;
			curp->next = p;
		}
		*_head = head;
		*_tail = tail;
	}

	ListNode *insertionSortList(ListNode *head) {
		if (head == 0)
			return head;
		ListNode *out_head = head;
		ListNode *out_tail = head;
		head = head->next;
		while (head) {
			ListNode *tmp = head;
			head = head->next;
			insert(&out_head, &out_tail, tmp);
		}
		out_tail->next = 0;
		return out_head;
	}

	void printList(ListNode *head) {
		while (head) {
			cout << head->val << " ";
			head = head->next;
		}
		cout << endl;
	}
};

int main()
{
	ListNode *p1 = new ListNode(4);
	ListNode *p2 = new ListNode(2);
	ListNode *p3 = new ListNode(1);
	ListNode *p4 = new ListNode(3);
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p4->next = 0;
	Solution solution;
	solution.insertionSortList(p1);

	return 0;
}
