/*
http://oj.leetcode.com/problems/minimum-path-sum/
Mon Feb  3 18:35:01 EST 2014


Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int minPathSum(vector<vector<int> > &grid) {
		if (grid.size() == 0)
			return 0;
		vector<int> dp(grid[0]);
		if (dp.size() == 0)
			return 0;
		for (size_t j = 1; j < dp.size(); ++j) {
			dp[j] += dp[j-1];
		}
		for (size_t i = 1; i < grid.size(); ++i) {
			dp[0] += grid[i][0];
			for (size_t j = 1; j < dp.size(); ++j) {
				dp[j] = grid[i][j] + min(dp[j-1], dp[j]);
			}
		}
		return dp.back();
	}
};

int main()
{
	vector<vector<int>> grid = {{1,3,1},
				    {1,5,1},
				    {4,2,1}};
	Solution s;
	cout << s.minPathSum(grid) << endl;
        return 0;
}
