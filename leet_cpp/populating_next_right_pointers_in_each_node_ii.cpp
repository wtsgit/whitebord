/*
http://oj.leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
Sun Jan 12 02:35:11 EST 2014


Populating Next Right Pointers in Each Node II

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous
solution still work?

Note:

    You may only use constant extra space.

For example,
Given the following binary tree,

	 1
       /  \
      2    3
     / \    \
    4   5    7

After calling your function, the tree should look like:

	 1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
*/

#include "leet.h"

class Solution {
public:
	void connect(TreeLinkNode *root) {
		TreeLinkNode *left_most = root;
		while (left_most) {
			TreeLinkNode *p = left_most;
			TreeLinkNode *q = 0;
			TreeLinkNode *n = 0;
			while (p) {
				n = 0;
				q = p->next;
				while (q && !n) {
					n = q->left ? q->left : q->right;
					q = q->next;
				}
				if (p->left)
					p->left->next = p->right ? p->right : n;
				if (p->right)
					p->right->next = n;
				p = p->next;
			}
			q = left_most;
			n = 0;
			while (q && !n) {
				n = q->left ? q->left : q->right;
				q = q->next;
			}
			left_most = n;
		}
	}
};

int main() {
	return 0;
}
