/*
http://oj.leetcode.com/problems/populating-next-right-pointers-in-each-node/
Sun Jan 12 01:47:05 EST 2014


Populating Next Right Pointers in Each Node

Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there
is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

    You may only use constant extra space.
    You may assume that it is a perfect binary tree (ie, all leaves
    are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

	 1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:

	 1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/

#include "leet.h"

class Solution {
public:
	void connect(TreeLinkNode *root) {
		TreeLinkNode *left_most = root;
		while (left_most) {
			TreeLinkNode *p = left_most;
			while (p != 0) {
				if (p->left)
					p->left->next = p->right;
				if (p->right && p->next)
					p->right->next = p->next->left;
				p = p->next;
			}
			left_most = left_most->left;
		}
	}
};

int main() {
	return 0;
}
