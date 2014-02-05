/*
http://oj.leetcode.com/problems/partition-list/
Fri Jan 24 01:44:11 EST 2014


Partition List

Given a linked list and a value x, partition it such that all nodes
less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in
each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	ListNode *partition(ListNode *head, int x) {
		ListNode dummy1(0);
		ListNode dummy2(0);
		dummy1.next = head;
		ListNode *tail = &dummy2;
		ListNode *p = &dummy1;
		while (p->next) {
			if (p->next->val < x) {
				tail->next = p->next;
				tail = p->next;
				p->next = p->next->next;
			}
			else {
				p = p->next;
			}
		}
		tail->next = dummy1.next;
		return dummy2.next;
	}
};

int main()
{
	return 0;
}
