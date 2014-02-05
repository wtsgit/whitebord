/*
http://oj.leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
Fri Jan 24 19:06:07 EST 2014


Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate
numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

#include "leet.h"

class Solution {
public:
	ListNode *deleteDuplicates(ListNode *head) {
		ListNode dummy(0);
		dummy.next = head;
		auto *p = &dummy;
		while (p->next && p->next->next) {
			if (p->next->val == p->next->next->val) {
				auto x = p->next->val;
				while (p->next && p->next->val == x) {
					auto q = p->next;
					p->next = p->next->next;
					delete q;
				}
			}
			else {
				p = p->next;
			}
		}
		return dummy.next;
	}
};

int main() {
	return 0;
}
