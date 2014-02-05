/*
http://oj.leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
Tue Jan 21 00:11:47 EST 2014


Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the zigzag level order traversal of its
nodes' values. (ie, from left to right, then right to left for the
next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:

[
  [3],
  [20,9],
  [15,7]
]

confused what "{1,#,2,3}" means? > read more on how binary tree is serialized on OJ.
*/
#include <iostream>
#include <vector>
#include <deque>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
		vector<vector<int> > result;
		if (root == nullptr)
			return result;
		deque<TreeNode *> dq;
		dq.push_back(root);
		deque<TreeNode *> new_dq;
		bool left_to_right = true;
		while (!dq.empty()) {
			new_dq.clear();
			result.emplace_back();
			auto &v = result.back();
			for (auto p : dq) {
				auto first = p->left;
				auto second = p->right;
				if (left_to_right == false)
					swap(first, second);
				if (first)
					new_dq.push_front(first);
				if (second)
					new_dq.push_front(second);
				v.push_back(p->val);
			}
			left_to_right = !left_to_right;
			dq = std::move(new_dq);
		}
		return result;
	}
};

int main() {
	return 0;
}
