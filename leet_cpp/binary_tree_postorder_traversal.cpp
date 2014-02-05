/*
http://oj.leetcode.com/problems/binary-tree-postorder-traversal/
Thu Jan  2 19:54:51 EST 2014


Binary Tree Postorder Traversal

Given a binary tree, return the postorder traversal of its nodes' values.
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
	vector<int> postorderTraversal(TreeNode *root)
	{
		stack<TreeNode *> s;
		vector<int> ret;
		TreeNode *cur = root;
		TreeNode *prev = 0;
		while (cur || !s.empty()) {
			if (cur) {
				s.push(cur);
				cur = cur->left ? cur->left : cur->right;
				prev = 0;
			}
			else if (prev == s.top()->right) {
				ret.push_back(s.top()->val);
				prev = s.top();
				s.pop();
			}
			else {
				cur = s.top()->right;
				prev = 0;
			}
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

	vector<int> res = sol.postorderTraversal(p1);
	copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}
