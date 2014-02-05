/*
http://oj.leetcode.com/problems/validate-binary-search-tree/
Mon Jan 20 17:50:32 EST 2014


Validate Binary Search Tree

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less
    than the node's key.

    The right subtree of a node contains only nodes with keys greater
    than the node's key.

    Both the left and right subtrees must also be binary search trees.
*/

#include <iostream>
#include <climits>
#include "leet.h"

class Solution {
public:
	bool isValidBSTSub(TreeNode *root, int lower, int upper) {
		if (root == nullptr)
			return true;
		if (root->val >= upper || root->val <= lower)
			return false;
		if (root->left) {
			if (root->left->val >= root->val)
				return false;
			if (!isValidBSTSub(root->left, lower, root->val))
				return false;
		}
		if (root->right) {
			if (root->right->val <= root->val)
				return false;
			if (!isValidBSTSub(root->right, root->val, upper))
				return false;
		}
		return true;
	}
	bool isValidBST(TreeNode *root) {
		return isValidBSTSub(root, INT_MIN, INT_MAX);
	}
};

int main()
{
	return 0;
}
