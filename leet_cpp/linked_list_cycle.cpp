/*
http://oj.leetcode.com/problems/linked-list-cycle/
Fri Jan  3 19:54:16 EST 2014


Linked List Cycle

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?
*/

#include <iostream>
#include "leet.h"

class Solution {
public:
	bool hasCycle(ListNode *head) {
		if (!head)
			return false;

		ListNode *pfast = head;
		ListNode *pslow = head;
		while (pfast->next && pfast->next->next) {
			pslow = pslow->next;
			pfast = pfast->next->next;
			if (pslow == pfast)
				return true;
		}
		return false;
	}
};

int main()
{
	return 0;
}
