/*
http://oj.leetcode.com/problems/flatten-binary-tree-to-linked-list/
Tue Jan 14 19:52:06 EST 2014


Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

For example,
Given

	 1
	/ \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:

   1
    \
     2
      \
       3
	\
	 4
	  \
	   5
	    \
	     6

Hints:

If you notice carefully in the flattened tree, each node's right
child points to the next node of a pre-order traversal.
*/

#include <iostream>
#include "leet.h"

class Solution {
public:
	void flattenSubtree(TreeNode *&first, TreeNode *&last, TreeNode *node) {
		first = node;
		last = node;
		TreeNode *lc = node->left;
		TreeNode *rc = node->right;
		node->left = 0;
		node->right = 0;
		TreeNode *f;
		TreeNode *l;
		if (lc) {
			flattenSubtree(f, l, lc);
			last->right = f;
			last = l;
		}
		if (rc) {
			flattenSubtree(f, l, rc);
			last->right = f;
			last = l;
		}
	}

	void flatten(TreeNode *root) {
		if (root) {
			TreeNode *first;
			TreeNode *last;
			flattenSubtree(first, last, root);
		}
	}
};

int main()
{
	return 0;
}
