/*
http://oj.leetcode.com/problems/balanced-binary-tree/
Wed Dec 18 19:35:42 EST 2013


Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a
binary tree in which the depth of the two subtrees of every node
never differ by more than 1.
*/
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "leet.h"

using namespace std;

class Solution {
public:
	pair<int, bool> treeHeight(const TreeNode *root)
	{
		int hl = 0;
		int hr = 0;

		if (root->left) {
			pair<int, bool> ret = treeHeight(root->left);
			if (!ret.second)
				return make_pair(0, false);
			hl = ret.first + 1;
		}
		if (root->right) {
			pair<int, bool> ret = treeHeight(root->right);
			if (!ret.second)
				return make_pair(0, false);
			hr = ret.first + 1;
		}
		if (abs(hl - hr) <= 1) {
			return make_pair(max(hl, hr), true);
		}
		return make_pair(0, false);
	}

	bool isBalanced(TreeNode *root) {
		if (!root)
			return true;
		pair<int, bool> ret = treeHeight(root);
		return ret.second;
	}
};

int main()
{
	return 0;
}
