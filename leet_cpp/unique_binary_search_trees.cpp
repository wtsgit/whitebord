/*
http://oj.leetcode.com/problems/unique-binary-search-trees/
Mon Jan 20 22:44:40 EST 2014


Unique Binary Search Trees

Given n, how many structurally unique BST's (binary search trees)
that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
public:
	int numTrees(int n) {
		assert(n >= 0);
		vector<size_t> count(n+1, 1);

		for (size_t i=1; i <= n; ++i) {
			size_t c = 0;
			for (size_t j = 0; j <= i-1; ++j) {
				c += count[j] * count[i-1-j];
			}
			count[i] = c;
		}
#if 1
		for (auto x : count)
			cout << x << " ";
		cout << endl;
#endif
		return count[n];
	}
};

int main() {
	Solution s;
	s.numTrees(10);
	return 0;
}
