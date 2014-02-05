/*
http://oj.leetcode.com/problems/binary-tree-level-order-traversal/
Mon Jan 20 23:57:25 EST 2014


Binary Tree Level Order Traversal

Given a binary tree, return the level order traversal of its nodes'
values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
]

confused what "{1,#,2,3}" means? > read more on how binary tree is
serialized on OJ.
*/
#include <iostream>
#include <vector>
#include <queue>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<vector<int> > levelOrder(TreeNode *root) {
		vector<vector<int> > result;
		if (root == nullptr)
			return result;
		typedef queue<TreeNode *> queue_type;
		queue_type cur;
		cur.push(root);
		while (!cur.empty()) {
			vector<int> v;
			queue_type next;
			while (!cur.empty()) {
				v.push_back(cur.front()->val);
				if (cur.front()->left)
					next.push(cur.front()->left);
				if (cur.front()->right)
					next.push(cur.front()->right);
				cur.pop();
			}
			cur = next;
			result.push_back(v);
		}
		return result;
	}
};

int main() {
	return 0;
}
