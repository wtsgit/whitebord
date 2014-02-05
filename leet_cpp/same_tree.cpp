/*
http://oj.leetcode.com/problems/same-tree/
Tue Jan 14 21:49:32 EST 2014


Same Tree

Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally
identical and the nodes have the same value.
*/

#include "leet.h"

class Solution {
public:
	bool isSameTree(TreeNode *p, TreeNode *q) {
		if (p == nullptr || q == nullptr)
			return p == q;
		if (p->val == q->val)
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		return false;
	}
};

int main() {
	return 0;
}
