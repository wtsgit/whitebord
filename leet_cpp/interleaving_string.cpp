/*
http://oj.leetcode.com/problems/interleaving-string/
Mon Jan 20 22:42:26 EST 2014


Interleaving String

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:

	bool isInterleave(string s1, string s2, string s3) {
		if (s3.size() == 0)
			return s1.size() == 0 && s2.size() == 0;
		if (s1.size() + s2.size() != s3.size())
			return false;
		vector<size_t> dp;
		dp.emplace_back(s1.size());
		for (size_t k = s3.size(); k > 0; --k) {
			vector<size_t> new_dp;
			for (size_t i : dp) {
				size_t l1 = s1.size() - i;
				size_t l3 = s3.size() - k;
				size_t j = s2.size() - (l3 - l1);
				if (i > 0 && s3[k-1] == s1[i-1]) {
					if (new_dp.empty() || new_dp.back() != i-1)
						new_dp.emplace_back(i-1);
				}
				if (j > 0 && s3[k-1] == s2[j-1])
					new_dp.emplace_back(i);
			}
			dp = new_dp;
#if 0
			cout << k-1 << ": ";
			for (auto x : dp)
				cout << x << " ";
			cout << endl;
#endif
		}

		return !dp.empty();
	}
};

int main()
{
	Solution s;
	cout << s.isInterleave("aabcc", "dbbca", "aadbbcbcac") << endl;
	cout << "========================================================================" << endl;
	cout << s.isInterleave("aabcc", "dbbca", "aadbbbaccc") << endl;
	return 0;
}
