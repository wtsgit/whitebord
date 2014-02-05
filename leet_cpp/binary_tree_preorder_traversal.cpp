/*
http://oj.leetcode.com/problems/binary-tree-preorder-traversal/
Thu Jan  2 21:38:41 EST 2014


Binary Tree Preorder Traversal

Given a binary tree, return the preorder traversal of its nodes' values.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<int> preorderTraversal(TreeNode *root)
	{
		vector<int> ret;
		if (root == 0)
			return ret;

		stack<TreeNode *> s;
		s.push(root);
		while (!s.empty()) {
			TreeNode *cur = s.top();
			s.pop();
			ret.push_back(cur->val);
			if (cur->right)
				s.push(cur->right);
			if (cur->left)
				s.push(cur->left);
		}

		return ret;
	}
};

int main()
{
	Solution sol;

	TreeNode *p1 = new TreeNode(2);
	TreeNode *p2 = new TreeNode(0);
	TreeNode *p3 = new TreeNode(1);
	p1->left = p2;
	p1->right = p3;

	vector<int> res = sol.preorderTraversal(p1);
	copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}
