/*
http://oj.leetcode.com/problems/reorder-list/
Thu Jan  2 21:46:12 EST 2014


Reorder List

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

{l0} -> {l0}
{l0, l1} -> {l0, l1}
{l0, l1, l2} -> {l0, l2, l1}
{l0, l1, l2, l3} -> {l0, l3, l1, l2}
{l0, l1, l2, l3, l4} -> {l0, l4, l1, l3, l2}
*/

#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	// Find middle node.
	// The midle node is the node in the middle if number of of nodes is odd,
	// or the last node of first half if the number is even.
	ListNode *findMid(ListNode *head) {
		if (head == 0)
			return 0;
		ListNode *slow = head;
		ListNode *fast = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}

	// Reverse single linked list in-place.
	ListNode *reverseList(ListNode *head) {
		ListNode *p = head;
		head = 0;
		while (p) {
			ListNode *q = p->next;
			p->next = head;
			head = p;
			p = q;
		}
		return head;
	}

	// Interlace 2 lists. L2 is not longer than l1.
	ListNode *interlaceLists(ListNode *l1, ListNode *l2) {
		ListNode *head = l1;
		while (l2) {
			ListNode *ptmp = l1->next;
			l1->next = l2;
			l2 = l2->next;
			l1->next->next = ptmp;
			l1 = ptmp;
		}
		return head;
	}

	void reorderList(ListNode *head) {
		if (head == 0)
			return;
		ListNode *mid = findMid(head);
		ListNode *secondHalf = mid->next;
		mid->next = 0;
		secondHalf = reverseList(secondHalf);
		(void)interlaceLists(head, secondHalf);
	}
};

int main()
{
	ListNode *p1 = new ListNode(1);
	ListNode *p2 = new ListNode(2);
	ListNode *p3 = new ListNode(3);
	ListNode *p4 = new ListNode(4);
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p4->next = 0;
	Solution solution;
	solution.reorderList(p1);
	while (p1) {
		cout << p1->val;
		p1 = p1->next;
	}
	cout << endl;
	return 0;
}
