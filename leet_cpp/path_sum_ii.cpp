/*
http://oj.leetcode.com/problems/path-sum-ii/
Tue Jan 14 20:42:54 EST 2014


Path Sum II

Given a binary tree and a sum, find all root-to-leaf paths where
each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,

	      5
	     / \
	    4   8
	   /   / \
	  11  13  4
	 /  \    / \
	7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]
*/

#include <vector>
#include "leet.h"

using namespace std;

class Solution {
public:
	void pathSumSubTree(vector<vector<int> > &coll, vector<int> path, TreeNode *node, int sum) {
		if (node == nullptr)
			return;
		if (node->left == nullptr && node->right == nullptr) {
			if (sum == node->val) {
				path.push_back(node->val);
				coll.push_back(path);
			}
			return;
		}
		path.push_back(node->val);
		sum -= node->val;
		pathSumSubTree(coll, path, node->left, sum);
		pathSumSubTree(coll, path, node->right, sum);
	}

	vector<vector<int> > pathSum(TreeNode *root, int sum) {
		vector<vector<int> > coll;
		vector<int> path;
		pathSumSubTree(coll, path, root, sum);
		return coll;
	}
};


int main() {
	return 0;
}
