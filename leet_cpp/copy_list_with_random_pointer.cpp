/*
http://oj.leetcode.com/problems/copy-list-with-random-pointer/
Sat Jan  4 21:09:37 EST 2014


Copy List with Random Pointer

A linked list is given such that each node contains an additional
random pointer which could point to any node in the list or null.

Return a deep copy of the list.
*/

#include <cassert>
#include <iostream>
#include "leet.h"

class Solution {
private:
	void insertAfter(RandomListNode *node, RandomListNode *p) {
		assert(node);
		assert(p);
		RandomListNode *ptmp = node->next;
		node->next = p;
		p->next = ptmp;
	}

	RandomListNode *detachAfter(RandomListNode *node) {
		assert(node);
		RandomListNode *p = node->next;
		if (p) {
			node->next = p->next;
		}
		return p;
	}

	void appendNode(RandomListNode *&head, RandomListNode *&tail, RandomListNode *p) {
		assert(p);
		if (tail == 0) {
			head = tail = p;
		}
		else {
			tail->next = p;
			tail = p;
		}
		p->next = 0;
	}

	void duplicatNodes(RandomListNode *node) {
		while (node) {
			RandomListNode *ptmp = node->next;
			insertAfter(node, new RandomListNode(node->label));
			node = ptmp;
		}
	}

	void copyRandomPointers(RandomListNode *node) {
		while (node) {
			assert(node->next);
			if (node->random) {
				node->next->random = node->random->next;
			}
			node = node->next->next;
		}
	}

	RandomListNode *deinterleaveNodes(RandomListNode *node) {
		RandomListNode *newhead = 0;
		RandomListNode *newtail = 0;
		while (node) {
			appendNode(newhead, newtail, detachAfter(node));
			node = node->next;
		}
		return newhead;
	}

public:
	RandomListNode *copyRandomList(RandomListNode *head) {
		duplicatNodes(head);
		copyRandomPointers(head);
		return deinterleaveNodes(head);
	}
};

int main()
{
	return 0;
}
