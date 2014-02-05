/*
http://oj.leetcode.com/problems/maximum-depth-of-binary-tree/
Tue Jan 21 20:02:35 EST 2014


Maximum Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path
from the root node down to the farthest leaf node.
*/

#include <iostream>
#include "leet.h"

using namespace std;

class Solution {
public:
	int maxDepth(TreeNode *root) {
		if (root == nullptr)
			return 0;
		return 1 + max(maxDepth(root->left), maxDepth(root->right));
	}
};

int main() {
	return 0;
}
