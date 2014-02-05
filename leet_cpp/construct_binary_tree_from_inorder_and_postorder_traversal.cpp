/*
http://oj.leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
Tue Jan 21 23:11:22 EST 2014


Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the
binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "leet.h"

using namespace std;

class Solution {
public:
	typedef vector<int>::const_iterator vicit_type;
	typedef vector<int>::const_reverse_iterator vicrit_type;
	TreeNode *buildTreeSub(vector<int> &inorder, vicit_type istart, vicit_type iend,
				vector<int> &postorder, vicrit_type &prstart) {
		if (istart == iend)
			return nullptr;
		assert(prstart != postorder.crend());
		auto root = new TreeNode(*prstart);
		auto rootloc = find(istart, iend, *prstart);
		assert(rootloc != iend);
		++prstart;
		root->right = buildTreeSub(inorder, rootloc+1, iend, postorder, prstart);
		root->left = buildTreeSub(inorder, istart, rootloc, postorder, prstart);
		return root;
	}

	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		auto it = postorder.crbegin();
		return buildTreeSub(inorder, inorder.cbegin(), inorder.cend(),
					postorder, it);
	}
};

int main() {
	return 0;
}
