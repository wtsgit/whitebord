/*
http://oj.leetcode.com/problems/minimum-depth-of-binary-tree/
Tue Jan 14 20:46:52 EST 2014


Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path
from the root node down to the nearest leaf node.
*/

#include <iostream>
#include <climits>
#include "leet.h"

using namespace std;

class Solution {
public:
	int minDepthSubTree(TreeNode *root) {
		if (root == nullptr)
			return INT_MAX;
		if (root->left == nullptr && root->right == nullptr)
			return 1;
		return 1+min(minDepth(root->left), minDepth(root->right));
	}

	int minDepth(TreeNode *root) {
		if (root == nullptr)
			return 0;
		return minDepthSubTree(root);
	}
};

int main()
{
	return 0;
}
