/*
http://oj.leetcode.com/problems/unique-paths-ii/
Thu Feb  6 00:16:32 EST 2014


Unique Paths II

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many
unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in
the grid.

For example,

There is one obstacle in the middle of a 3x3 grid as illustrated
below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]

The total number of unique paths is 2.

Note: m and n will be at most 100.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
		const size_t m = obstacleGrid.size();
		if (m == 0)
			return 0;
		const size_t n = obstacleGrid[0].size();
		if (n == 0)
			return 0;
		vector<size_t> dp(n, 0);
		for (size_t j = 0; j < n; ++j) {
			if (obstacleGrid[0][j] == 0) {
				dp[j] = 1;
			}
			else {
				break;
			}
		}
		for (size_t i = 1; i < m; ++i) {
			dp[0] = (obstacleGrid[i][0] == 1 || dp[0] == 0) ? 0 : 1;
			for (size_t j = 1; j < n; ++j) {
				if (obstacleGrid[i][j]) {
					dp[j] = 0;
				}
				else {
					dp[j] += dp[j-1];
				}
			}
		}
		return (int)dp.back();
        }
};

int main()
{
	{
		vector<vector<int>> grid{ {0, 0, 0},
					  {0, 1, 0},
					  {0, 0, 0} };
		Solution s;
		cout << s.uniquePathsWithObstacles(grid) << endl;
	}
	{
		vector<vector<int>> grid{ {0},
					  {0} };
		Solution s;
		cout << s.uniquePathsWithObstacles(grid) << endl;
	}
        return 0;
}
