/*
http://oj.leetcode.com/problems/rotate-list/
Thu Feb  6 01:29:20 EST 2014


Rotate List

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/

#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	ListNode *rotateRight(ListNode *head, int k) {
		if (head == nullptr)
			return head;
		int n = 0;
		auto p = head;
		auto q = head;
		while (p) {
			++n;
			q = p;
			p = p->next;
		}
		k %= n;
		if (k == 0)
			return head;
		q->next = head;
		n -= k;
		while (n > 0) {
			q = head;
			head = head->next;
			--n;
		}
		q->next = nullptr;
		return head;
	}
};

int main()
{
        return 0;
}
