/*
http://oj.leetcode.com/problems/distinct-subsequences/
Sun Jan 12 12:49:02 EST 2014


Distinct Subsequences

Given a string S and a string T, count the number of distinct
subsequences of T in S.

A subsequence of a string is a new string which is formed from the
original string by deleting some (can be none) of the characters
without disturbing the relative positions of the remaining characters.
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

using namespace std;

class Solution {
public:
	int numDistinct(string S, string T) {
		vector<int> v(T.size()+1, 0);
		v[T.size()] = 1;
		size_t i = S.size();
		while (i) {
			for (size_t j = 0; j < T.size(); ++j) {
				if (S[i-1] == T[j])
					v[j] += v[j+1];
			}
			--i;
		}

		return v[0];
	}
};

int main(int argc, char **argv)
{
	if (argc < 3)
		return 0;
	Solution s;
	cout << s.numDistinct(argv[1], argv[2]) << endl;
	return 0;
}

