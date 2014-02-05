/*
http://oj.leetcode.com/problems/merge-two-sorted-lists/
Mon Feb  3 17:56:50 EST 2014


Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. The new
list should be made by splicing together the nodes of the first two
lists.
*/
#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		ListNode dummy(0);
		ListNode *p = &dummy;
		while (l1 || l2) {
			if (l1 && (!l2 || l1->val < l2->val)) {
				p->next = l1;
				l1 = l1->next;
			}
			else {
				p->next = l2;
				l2 = l2->next;
			}
			p = p->next;
		}
		return dummy.next;
	}
};

int main()
{
        return 0;
}
