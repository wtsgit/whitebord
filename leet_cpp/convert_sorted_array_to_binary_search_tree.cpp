/*
http://oj.leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
Thu Jan 16 23:56:53 EST 2014


Convert Sorted Array to Binary Search Tree

Given an array where elements are sorted in ascending order, convert
it to a height balanced BST.
*/
#include <vector>
#include <cassert>
#include "leet.h"

using namespace std;

class Solution {
public:
	TreeNode *sortedArrayToBSTSubTree(const vector<int> &num, const size_t s, const size_t n) {
		if (n == 0)
			return nullptr;

		size_t k = 0;
		size_t n_left = 0;
		size_t n_right = 0;
		while (1 << (k+1) <= n+1) {
			++k;
		}
		// 2^(k+1) > n+1 => 2^(k+1) - 1 > n => 2^k - 1 <= n
		// n = 0 => k = 0, n_left = 0; (1<<k)/2 = 0
		// n = 1 => k = 1, n_left = 0; (1<<k)/2 = 1
		// n = 2 => k = 1, n_left = 0; (1<<k)/2 = 1
		// n = 3 => k = 2, n_left = 1; (1<<k)/2 = 2
		// n = 4 => k = 2, n_left = 1; (1<<k)/2 = 2
		// n = 5 => k = 2, n_left = 1; (1<<k)/2 = 2
		n_left = ((1<<k)-1)/2;
		if (n - 2*n_left - 1 >= (1<<k)/2)
			n_left += (1<<k)/2;
		else
			n_left += n - 2*n_left - 1;
		n_right = n-n_left-1;

		assert(n_left <= n-1);
		assert(n_left+1 <= n-1 || n_right == 0);
		TreeNode *node = new TreeNode(num[s+n_left]);
		node->left = sortedArrayToBSTSubTree(num, s, n_left);
		node->right = sortedArrayToBSTSubTree(num, s+n_left+1, n_right);
		return node;
	}

	TreeNode *sortedArrayToBST(vector<int> &num) {
		return sortedArrayToBSTSubTree(num, 0, num.size());
	}
};

int main(int argc, char **argv) {
	Solution s;

	vector<int> vi;
	s.sortedArrayToBST(vi);

	vi={1};
	s.sortedArrayToBST(vi);

	vi={1,2};
	s.sortedArrayToBST(vi);

	vi={1,2,3};
	s.sortedArrayToBST(vi);

	vi={1,2,3,4};
	s.sortedArrayToBST(vi);

	vi={1,2,3,4,5};
	s.sortedArrayToBST(vi);

	vi={1,2,3,4,5,6};
	s.sortedArrayToBST(vi);

	vi={1,2,3,4,5,6,7};
	s.sortedArrayToBST(vi);

	return 0;
}
