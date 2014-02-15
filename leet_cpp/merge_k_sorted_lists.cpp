/*
http://oj.leetcode.com/problems/merge-k-sorted-lists/
Sat Feb 15 17:17:45 EST 2014


Merge k Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze
and describe its complexity.
*/
#include <vector>
#include <queue>
#include <iostream>
#include <functional>
#include "leet.h"

using namespace std;

struct PQGreater {
	bool operator()(const ListNode * a, const ListNode * b) const {
		return a->val > b->val;
	}
};

class Solution {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		ListNode dummy(0);
		auto tail = &dummy;
		priority_queue<ListNode *, std::vector<ListNode *>, PQGreater> h;
		for (auto p : lists)
			if (p) h.push(p);
		while (!h.empty()) {
			auto p = h.top();
			auto q = p->next;
			h.pop();
			tail->next = p;
			tail = p;
			if (q) h.push(q);
		}
		return dummy.next;
	}
};

int main() {
	vector<ListNode *> v;
	{
		ListNode *p1 = new ListNode(10);
		ListNode *p2 = new ListNode(20);
		ListNode *p3 = new ListNode(30);
		ListNode *p4 = new ListNode(40);
		p1->next = p2;
		p2->next = p3;
		p3->next = p4;
		p4->next = nullptr;
		v.push_back(p1);
	}
	{
		ListNode *p1 = new ListNode(11);
		ListNode *p2 = new ListNode(22);
		ListNode *p3 = new ListNode(33);
		ListNode *p4 = new ListNode(44);
		p1->next = p2;
		p2->next = p3;
		p3->next = p4;
		p4->next = nullptr;
		v.push_back(p1);
	}

	Solution s;
	auto mp = s.mergeKLists(v);
	cout << "merged" << endl;
	while (mp) {
		cout << mp->val << " ";
		mp = mp->next;
	}
	cout << endl;
	return 0;
}
