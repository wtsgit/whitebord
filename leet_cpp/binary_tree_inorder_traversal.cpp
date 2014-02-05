/*
http://oj.leetcode.com/problems/binary-tree-inorder-traversal/
Fri Jan 31 18:14:05 EST 2014


Binary Tree Inorder Traversal

Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/
#include <iostream>
#include <vector>
#include <stack>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<int> inorderTraversal(TreeNode *root) {
		vector<int> v;
		TreeNode *p = root;
		stack<TreeNode *> st;
		while (p || !st.empty()) {
			if (p == nullptr) {
				p = st.top();
				st.pop();
				v.push_back(p->val);
				p = p->right;
			}
			else {
				st.push(p);
				p = p->left;
			}
		}
		return v;
	}
};

int main()
{
        return 0;
}
