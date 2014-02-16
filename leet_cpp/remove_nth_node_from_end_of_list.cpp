/*
http://oj.leetcode.com/problems/remove-nth-node-from-end-of-list/
Sat Feb 15 19:45:38 EST 2014


Remove Nth Node From End of List

Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass.
*/

#include <iostream>
#include "leet.h"

class Solution {
public:
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		if (n <= 0)
			return head;
		if (head == nullptr)
			return head;
		ListNode dummy(0);
		dummy.next = head;
		auto adv = head;
		size_t count = 0;
		while (adv && count < (size_t)n) {
			adv = adv->next;
			++count;
		}
		if (count < (size_t)n)
			return head;
		auto p = head;
		auto q = &dummy;
		while (adv) {
			q = p;
			p = p->next;
			adv = adv->next;
		}
		q->next = p->next;
		delete p;
		return dummy.next;
	}
};

int main() {
	return 0;
}
