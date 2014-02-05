/*
http://oj.leetcode.com/problems/unique-binary-search-trees-ii/
Mon Jan 20 23:03:38 EST 2014


Unique Binary Search Trees II

Given n, generate all structurally unique BST's (binary search
trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

#include <iostream>
#include <vector>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<TreeNode *> generateSubTrees(size_t n, size_t l) {
		if (l == 0)
			return vector<TreeNode *>(1, nullptr);
		if (l == 1)
			return vector<TreeNode *>(1, new TreeNode(n));
		vector<TreeNode *> result;
		for (size_t i = 0; i <= l-1; ++i) {
			auto left = generateSubTrees(n, i);
			auto right = generateSubTrees(n+i+1, l-i-1);
			for (auto x : left) {
				for (auto y : right) {
					auto p = new TreeNode(n+i);
					p->left = x;
					p->right = y;
					result.push_back(p);
				}
			}
		}
		return result;
	}
	vector<TreeNode *> generateTrees(int n) {
		return generateSubTrees(1, n);
	}
};

int main()
{
	return 0;
}
