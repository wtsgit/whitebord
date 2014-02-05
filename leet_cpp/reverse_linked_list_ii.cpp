/*
http://oj.leetcode.com/problems/reverse-linked-list-ii/
Wed Jan 22 12:02:21 EST 2014


Reverse Linked List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.
*/

#include "leet.h"

class Solution {
public:
	ListNode *reverseBetween(ListNode *head, int m, int n) {
		if (m == n || head == nullptr)
			return head;
		ListNode dummy(0);
		dummy.next = head;
		ListNode *eob = &dummy;
		ListNode *p = head;
		int i = 1;
		while (i < m && p->next) {
			eob = p;
			p = p->next;
			++i;
		}
		ListNode *t = p;
		ListNode *h = p;
		ListNode *boe = p->next;
		while (i < n && boe) {
			p = boe;
			boe = p->next;
			p->next = h;
			h = p;
			++i;
		}
		eob->next = h;
		t->next = boe;
		return dummy.next;
	}
};

int main()
{
	return 0;
}
