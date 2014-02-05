/*
http://oj.leetcode.com/problems/swap-nodes-in-pairs/
Thu Jan 30 01:35:30 EST 2014


Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify
the values in the list, only nodes itself can be changed.
*/

#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	ListNode *swapPairs(ListNode *head) {
		ListNode dummy(0);
		dummy.next = head;
		ListNode *p = &dummy;
		ListNode *p0 = nullptr;
		ListNode *p1 = nullptr;
		while ((p0 = p->next) && (p1 = p0->next)) {
			ListNode *q = p1->next;
			p->next = p1;
			p1->next = p0;
			p0->next = q;
			p = p0;
		}
		return dummy.next;
	}
};

int main()
{
        return 0;
}
