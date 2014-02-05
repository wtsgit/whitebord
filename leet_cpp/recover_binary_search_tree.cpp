/*
http://oj.leetcode.com/problems/recover-binary-search-tree/
Mon Jan 20 17:51:57 EST 2014


Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you
devise a constant space solution?
*/
#include <iostream>
#include <stdexcept>
#include "leet.h"

using namespace std;

class Solution {
private:
	struct Inspector {
		TreeNode *bad1;
		TreeNode *bad2;
		TreeNode *prev;
		TreeNode *p;
		TreeNode *next;
		bool needMore() { return bad1 == nullptr || bad2 == nullptr; }
		void feed(TreeNode *node) {
			prev = p;
			p = next;
			next = node;
			if (bad1 == nullptr) {
				if (p && next && p->val > next->val)
					bad1 = p;
			}
			else if (bad2 == nullptr) {
				if (p && prev && p->val < prev->val) {
					if (next == nullptr || bad1->val < next->val)
						bad2 = p;
				}
			}
		}
	};

	void recoverTreeSub(Inspector &inspector, TreeNode *node) {
		if (node == nullptr)
			return;
		if (inspector.needMore())
			recoverTreeSub(inspector, node->left);
		if (inspector.needMore())
			inspector.feed(node);
		if (inspector.needMore())
			recoverTreeSub(inspector, node->right);
	}

public:
	void recoverTree(TreeNode *root) {
		if (root == nullptr)
			return;
		if (root->left == nullptr && root->right == nullptr)
			return;
		Inspector inspector{};
		recoverTreeSub(inspector, root);
		if (inspector.needMore())
			inspector.feed(nullptr);
		if (inspector.needMore())
			throw invalid_argument("No swapped pair found in tree.");
		swap(inspector.bad1->val, inspector.bad2->val);
	}
};

int main() {
	return 0;
}
