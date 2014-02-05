/*
http://oj.leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
Tue Jan 21 22:20:26 EST 2014


Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

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
	TreeNode *buildTreeSub(vector<int> &preorder, vicit_type &pstart,
				vector<int> &inorder, vicit_type istart, vicit_type iend) {
		if (istart == iend)
			return nullptr;
		assert(pstart != preorder.end());
		auto root = new TreeNode(*pstart);
		auto rootloc = find(istart, iend, *pstart);
		assert(rootloc != iend);
		++pstart;
		root->left = buildTreeSub(preorder, pstart, inorder, istart, rootloc);
		root->right = buildTreeSub(preorder, pstart, inorder, ++rootloc, iend);
		return root;
	}

	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
		auto it = preorder.cbegin();
		return buildTreeSub(preorder, it,
					inorder, inorder.begin(), inorder.end());
	}
};

int main() {
	Solution s;
	vector<int> preorder{1, 2};
	vector<int> inorder{2, 1};
	s.buildTree(preorder, inorder);
	return 0;
}
