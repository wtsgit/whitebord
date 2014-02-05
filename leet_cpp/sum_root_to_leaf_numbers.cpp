/*
http://oj.leetcode.com/problems/sum-root-to-leaf-numbers/
Tue Jan  7 13:55:40 EST 2014


Sum Root to Leaf Numbers

Given a binary tree containing digits from 0-9 only, each root-to-leaf
path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.
*/

#include <iostream>
#include "leet.h"

class Solution {
public:
	void sumNumbersRecursive(int &sum, int num, TreeNode *node) {
		if (node == 0)
			return;
		num = num * 10 + node->val;
		if (node->left == 0 && node->right == 0) {
			sum += num;
		}
		else {
			sumNumbersRecursive(sum, num, node->left);
			sumNumbersRecursive(sum, num, node->right);
		}
	}

	int sumNumbers(TreeNode *root) {
		int sum = 0;
		sumNumbersRecursive(sum, 0, root);
		return sum;
	}
};

int main()
{
	return 0;
}
