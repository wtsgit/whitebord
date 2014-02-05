/*
http://oj.leetcode.com/problems/binary-tree-maximum-path-sum/
Sat Jan 11 00:00:19 UTC 2014


Binary Tree Maximum Path Sum

Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6.
*/

#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	void maxSum(int &max_to_here, int &max_sum, TreeNode *node) {
		if (node == 0)
			return;

		if (node->left == 0 && node->right == 0) {
			max_to_here = node->val;
			max_sum = node->val;
			return;
		}

		if (node->left == 0 || node->right == 0) {
			maxSum(max_to_here, max_sum, node->left ? node->left : node->right);
			max_to_here = max(max_to_here + node->val, node->val);
			max_sum = max(max_sum, max_to_here);
			return;
		}

		int max_to_here_lc;
		int max_sum_lc;
		int max_to_here_rc;
		int max_sum_rc;

		maxSum(max_to_here_lc, max_sum_lc, node->left);
		maxSum(max_to_here_rc, max_sum_rc, node->right);
		max_to_here = max(max(max_to_here_lc, max_to_here_rc) + node->val, node->val);
		max_sum = node->val;
		if (max_to_here_lc > 0)
			max_sum += max_to_here_lc;
		if (max_to_here_rc > 0)
			max_sum += max_to_here_rc;
		max_sum = max(max(max_sum_lc, max_sum_rc), max_sum);
	}

	int maxPathSum(TreeNode *root) {
		int max_to_here = 0;
		int max_sum = 0;
		maxSum(max_to_here, max_sum, root);
		return  max_sum;
	}
};

int main()
{
	return 0;
}

