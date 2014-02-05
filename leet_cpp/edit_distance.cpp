/*
http://oj.leetcode.com/problems/edit-distance/
Mon Feb  3 10:58:33 EST 2014


Edit Distance

Given two words word1 and word2, find the minimum number of steps
required to convert word1 to word2. (each operation is counted as
1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int minDistance(string word1, string word2) {
		const size_t m = word1.size();
		const size_t n = word2.size();
		if (m == 0)
			return n;
		if (n == 0)
			return m;
		vector<vector<size_t>> dp(m+1);
		for (auto &v : dp)
			v.resize(n+1);
		for (size_t i = 0; i < n+1; ++i)
			dp[0][i] = i;
		for (size_t i = 0; i < m+1; ++i)
			dp[i][0] = i;

		for (size_t i = 1; i < m+1; ++i) {
			for (size_t j = 1; j < n+1; ++j) {
				auto c1 = word1[i-1];
				auto c2 = word2[j-1];
				if (c1 == c2) {
					dp[i][j] = dp[i-1][j-1];
				}
				else {
					size_t dist = ~(size_t)0;
					dist = min(dist, dp[i-1][j]+1);
					dist = min(dist, dp[i][j-1]+1);
					dist = min(dist, dp[i-1][j-1]+1);
					dp[i][j] = dist;
				}
			}
		}
		return dp[m][n];
	}
};

int main(int argc, char **argv)
{
	if (argc < 3)
		return 1;
	Solution s;
	cout << s.minDistance(argv[1], argv[2]) << endl;
        return 0;
}
