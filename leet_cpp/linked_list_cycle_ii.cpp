/*
http://oj.leetcode.com/problems/linked-list-cycle-ii/
Fri Jan  3 19:54:16 EST 2014


Linked List Cycle II

Given a linked list, return the node where the cycle begins. If
there is no cycle, return null.

Follow up:
Can you solve it without using extra space?
*/

#include <iostream>
#include "leet.h"

class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		if (!head)
			return 0;
		ListNode *pfast = head;
		ListNode *pslow = head;
		bool hasCycle = false;
		while (pfast->next && pfast->next->next) {
			pslow = pslow->next;
			pfast = pfast->next->next;
			if (pslow == pfast) {
				hasCycle = true;
				break;
			}
		}
		if (hasCycle) {
			pslow = head;
			while (pslow != pfast) {
				pslow = pslow->next;
				pfast = pfast->next;
			}
			return pslow;
		}
		return 0;
	}
};

int main()
{
	return 0;
}
