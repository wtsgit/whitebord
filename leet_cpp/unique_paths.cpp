/*
http://oj.leetcode.com/problems/unique-paths/
Thu Feb  6 00:01:37 EST 2014


Unique Paths

A robot is located at the top-left corner of a m x n grid (marked
'Start' in the diagram below).

The robot can only move either down or right at any point in time.
The robot is trying to reach the bottom-right corner of the grid
(marked 'Finish' in the diagram below).

How many possible unique paths are there?

Above is a 3 x 7 grid. How many possible unique paths are there?

Note: m and n will be at most 100.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int uniquePaths(int m, int n) {
		if (m <= 0 || n <= 0)
			return 0;
		vector<int> dp(n, 1);
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				dp[j] += dp[j-1];
			}
		}
		return dp.back();
	}
};

int main()
{
        return 0;
}
