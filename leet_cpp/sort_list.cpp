/*
http://oj.leetcode.com/problems/sort-list/
Wed Jan  1 23:43:57 EST 2014


Sort List

Sort a linked list in O(n log n) time using constant space complexity.
*/

#include <iostream>
#include <random>
#include <cstdlib>
#include "leet.h"

using namespace std;

// O(log n) space.
class Solution_Recursive {
public:
	ListNode *sortList(ListNode *head) {
		if (head == 0 || head->next == 0)
			return head;
		ListNode *mid = findMiddle(head);
		ListNode *secondHalf = mid->next;
		mid->next = 0;
		head = sortList(head);
		secondHalf = sortList(secondHalf);
		return mergeSortedLists(head, secondHalf);
	}

	// return the tail of the first half.
	ListNode *findMiddle(ListNode *head) {
		if (head == 0)
			return head;
		ListNode *slow = head;
		ListNode *fast = head;
		while (fast->next && fast->next->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}

	ListNode *mergeSortedLists(ListNode *l1, ListNode *l2) {
		ListNode *output_list = new ListNode(0); // dummy
		ListNode *output_tail = output_list;
		while (l1 && l2) {
			if (l1-> val < l2->val) {
				output_tail->next = l1;
				l1 = l1->next;
			}
			else {
				output_tail->next = l2;
				l2 = l2->next;
			}
			output_tail = output_tail->next;
		}
		output_tail->next = l1 ? l1 : l2;
		ListNode *tmp_list = output_list;
		output_list = output_list->next;
		delete tmp_list;
		return output_list;
	}
};

void dumpList(ListNode *head) {
	while (head) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

// O(1) space.
class Solution {
public:
	ListNode *sortList(ListNode *head) {
		if (head == nullptr || head->next == nullptr)
			return head;

		ListNode dummy(0);
		dummy.next = head;
		head = &dummy;

		size_t seg_size = 1;
		size_t n_merge = 0;
		do {
			auto tail = head;
			auto q = head->next;
			n_merge = 0;
			while (q) {
				auto p = q;
				size_t p_size = 0;
				size_t q_size = seg_size;
				while (p_size < seg_size && q) {
					q = q->next;
					++p_size;
				}
				while (p_size && q && q_size) {
					if (p->val < q->val) {
						tail->next = p;
						p = p->next;
						--p_size;
					}
					else {
						tail->next = q;
						q = q->next;
						--q_size;
					}
					tail = tail->next;
				}
				while (p_size) {
					tail->next = p;
					tail = tail->next;
					p = p->next;
					--p_size;
				}
				while (q && q_size) {
					tail->next = q;
					tail = tail->next;
					q = q->next;
					--q_size;
				}
				++n_merge;
			}
			tail->next = nullptr;
			seg_size *= 2;
		} while (n_merge > 1);

		return dummy.next;
	}
};

int main(int argc, char **argv) {
	if (argc < 2)
		return 1;

	int n = atoi(argv[1]);
	if (n <= 0)
		return 1;

	random_device rd;
	default_random_engine rng(rd());
	uniform_int_distribution<int> uniform_dist(-n, n);

	ListNode *head = nullptr;
	ListNode *tail = nullptr;
	for (size_t i = 0; i < n; ++i) {
		ListNode *node = new ListNode(uniform_dist(rng));
		if (head == nullptr) {
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
	}

	Solution s;
	dumpList(head);
	head = s.sortList(head);
	dumpList(head);

	return 0;
}
