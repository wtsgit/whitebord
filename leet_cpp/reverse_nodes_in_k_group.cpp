/*
http://oj.leetcode.com/problems/reverse-nodes-in-k-group/
Fri Feb 14 19:11:47 EST 2014


Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time
and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes
in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may
be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
*/

#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	ListNode *reverseKGroup(ListNode *head, int k) {
		ListNode *reversed_list_head = nullptr;
		ListNode *reversed_list_tail = nullptr;
		ListNode *kgroup_head = head;
		while (true) {
			size_t count = 0;
			auto p = kgroup_head;
			while (p && count < (size_t)k) {
				p = p->next;
				++count;
			}
			if (count == (size_t)k) {
				count = 0;
				ListNode *reversed_kgroup_head = nullptr;
				ListNode *reversed_kgroup_tail = nullptr;
				p = kgroup_head;
				while (p && count < (size_t)k) {
					ListNode *q = p->next;
					p->next = reversed_kgroup_head;
					reversed_kgroup_head = p;
					if (reversed_kgroup_tail == nullptr)
						reversed_kgroup_tail = p;
					p = q;
					++count;
				}
				if (reversed_list_head == nullptr)
					reversed_list_head = reversed_kgroup_head;
				else
					reversed_list_tail->next = reversed_kgroup_head;
				reversed_list_tail = reversed_kgroup_tail;
			}
			else {
				if (reversed_list_head == nullptr)
					reversed_list_head = kgroup_head;
				else
					reversed_list_tail->next = kgroup_head;
				break;
			}
			kgroup_head = p;
		}
		return reversed_list_head;
	}
};

int main() {
	return 0;
}
