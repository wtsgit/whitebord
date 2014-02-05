/*
http://oj.leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
Thu Jan 16 23:59:19 EST 2014


Convert Sorted List to Binary Search Tree

Given a singly linked list where elements are sorted in ascending
order, convert it to a height balanced BST.
*/

#include <iostream>
#include <cassert>
#include "leet.h"

using namespace std;

class Solution {
public:
	// Can also use BFS to build the tree.
	TreeNode *buildBST(const size_t s, const size_t n) {
		if (n == 0)
			return nullptr;

		size_t k = 0;
		size_t n_left = 0;
		size_t n_right = 0;
		while (1 << (k+1) <= n+1) {
			++k;
		}

		// 2^(k+1) > n+1 => 2^(k+1) - 1 > n => 2^k - 1 <= n
		// n = 0 => k = 0, n_left = 0; (1<<k)/2 = 0
		// n = 1 => k = 1, n_left = 0; (1<<k)/2 = 1
		// n = 2 => k = 1, n_left = 0; (1<<k)/2 = 1
		// n = 3 => k = 2, n_left = 1; (1<<k)/2 = 2
		// n = 4 => k = 2, n_left = 1; (1<<k)/2 = 2
		// n = 5 => k = 2, n_left = 1; (1<<k)/2 = 2

		n_left = ((1<<k)-1)/2;
		if (n - 2*n_left - 1 >= (1<<k)/2)
			n_left += (1<<k)/2;
		else
			n_left += n - 2*n_left - 1;
		n_right = n-n_left-1;

		assert(n_left <= n-1);
		assert(n_left+1 <= n-1 || n_right == 0);
		TreeNode *node = new TreeNode(s+n_left);
		node->left = buildBST(s, n_left);
		node->right = buildBST(s+n_left+1, n_right);

		return node;
	}

	void copyNodeVal(TreeNode *tn, ListNode *&ln) {
		if (tn == nullptr)
			return;
		copyNodeVal(tn->left, ln);
		tn->val = ln->val;
		ln = ln->next;
		copyNodeVal(tn->right, ln);
	}

	TreeNode *sortedListToBST(ListNode *head) {
		size_t n = 0;
		for (ListNode *lp = head; lp; ++n, lp = lp->next);
		TreeNode *root = buildBST(0, n);
		copyNodeVal(root, head);
		return root;
	}
};

int main()
{
	ListNode *p1 = new ListNode(1);
	ListNode *p2 = new ListNode(3);

	p1->next = p2;

	Solution s;
	TreeNode *root = s.sortedListToBST(p1);
	(void)root;
	return 0;
}
