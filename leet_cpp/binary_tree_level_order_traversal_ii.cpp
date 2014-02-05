/*
http://oj.leetcode.com/problems/binary-tree-level-order-traversal-ii/
Fri Jan 31 17:33:28 EST 2014


Binary Tree Level Order Traversal II

Given a binary tree, return the bottom-up level order traversal of
its nodes' values. (ie, from left to right, level by level from
leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its bottom-up level order traversal as:

[
  [15,7]
  [9,20],
  [3],
]
*/

#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<vector<int> > levelOrderBottom(TreeNode *root) {
		vector<vector<int>> vv;
		if (root == nullptr)
			return vv;
		vector<int> v;
		queue<TreeNode *> q;
		q.push(root);
		q.push(nullptr);
		while (!q.empty()) {
			auto p = q.front();
			q.pop();
			if (p) {
				v.push_back(p->val);
				if (p->left) q.push(p->left);
				if (p->right) q.push(p->right);
			}
			else {
				vv.push_back(std::move(v));
				v.clear();
				if (!q.empty())
					q.push(nullptr);
			}
		}
		//g++ ok, clang failed.
		//std::reverse(std::make_move_iterator(vv.begin()), std::make_move_iterator(vv.end()));
		std::reverse(vv.begin(), vv.end());
		return vv;
	}
};

int main()
{
        return 0;
}
