/*
http://oj.leetcode.com/problems/remove-duplicates-from-sorted-list/
Fri Jan 24 19:13:28 EST 2014


Remove Duplicates from Sorted List

Given a sorted linked list, delete all duplicates such that each
element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/

#include "leet.h"

class Solution {
public:
	ListNode *deleteDuplicates(ListNode *head) {
		if (head == nullptr)
			return head;
		auto p = head;
		while (p->next) {
			if (p->val == p->next->val) {
				while (p->next && p->next->val == p->val) {
					auto q = p->next;
					p->next = p->next->next;
					delete q;
				}
			}
			else {
				p = p->next;
			}
		}
		return head;
	}
};

int main() {
	return 0;
}
