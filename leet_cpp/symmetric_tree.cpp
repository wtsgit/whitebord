/*
http://oj.leetcode.com/problems/symmetric-tree/
Fri Jan 17 01:15:12 EST 2014


Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie,
symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following is not:

    1
   / \
  2   2
   \   \
   3    3

Note:
Bonus points if you could solve it both recursively and iteratively.
*/

#include <iostream>
#include <stack>
#include "leet.h"

using namespace std;

class Solution {
public:
	bool isSymmetricSub(const TreeNode *u, const TreeNode *v) {
		if (u == nullptr)
			return v == nullptr;
		if (v == nullptr)
			return u == nullptr;
		if (u->val != v->val)
			return false;
		return isSymmetricSub(u->left, v->right) && isSymmetricSub(u->right, v->left);
	}
	bool isSymmetric(TreeNode *root) {
		if (root == nullptr)
			return true;
		return isSymmetricSub(root->left, root->right);
	}
};

class SolutionIter {
public:
	bool isSymmetric(TreeNode *root) {
		if (root == nullptr)
			return true;
		stack<TreeNode *> s1;
		stack<TreeNode *> s2;
		s1.push(root->left);
		s2.push(root->right);
		while (true) {
			if (s1.empty())
				return s2.empty();
			if (s2.empty())
				return s1.empty();

			TreeNode *u = s1.top();
			s1.pop();
			TreeNode *v = s2.top();
			s2.pop();
			if (u == nullptr && v != nullptr)
				return false;
			if (v == nullptr && u != nullptr)
				return false;
			if (u == nullptr && v == nullptr)
				continue;
			if (u->val != v->val)
				return false;

			s1.push(u->right);
			s1.push(u->left);
			s2.push(v->left);
			s2.push(v->right);
		}
		return false;
	}
};

int main()
{
	return 0;
}

