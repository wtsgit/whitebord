/*
http://oj.leetcode.com/problems/scramble-string/
Thu Jan 23 21:08:34 EST 2014


Scramble String

Given a string s1, we may represent it as a binary tree by partitioning
it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
	   / \
	  a   t

To scramble the string, we may choose any non-leaf node and swap
its two children.

For example, if we choose the node "gr" and swap its two children,
it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
	   / \
	  a   t

We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and
"at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a

We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is
a scrambled string of s1.
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	bool isScramble(string s1, string s2) {
		if (s1.size() != s2.size())
			return false;
		if (s1.size() <= 1)
			return s1 == s2;

		unordered_map<char, unordered_set<size_t> > mp;
		for (size_t i = 0; i < s1.size(); ++i) {
			mp[s1[i]].insert(i);
		}

		vector<vector<unordered_set<size_t> > > dp(s2.size());
		dp[0].reserve(s2.size());
		for (size_t i = 0; i < s2.size(); ++i) {
			dp[0].push_back(mp[s2[i]]);
		}

		for (size_t len = 2; len <= s2.size(); ++len) {
			dp[len-1].resize(s2.size()-len+1);
			for (size_t i = 0; i <= s2.size()-len; ++i) {
				for (size_t j = i+1; j <= i+len-1; ++j) { // [i, i+len) => [i+1, i+len-1]
					size_t llen = j-i; //[i, j)
					size_t rlen = len-llen; //[j, i+len)
					auto &lset = dp[llen-1][i];
					auto &rset = dp[rlen-1][j];
					auto &nset = dp[len-1][i];
					for (auto k : lset) {
						if (rset.find(k+llen) != rset.end())
							nset.insert(k);
						if (k >= rlen && rset.find(k-rlen) != rset.end())
							nset.insert(k-rlen);
					}
				}
			}
		}
		return !dp[s2.size()-1][0].empty();
	}
};

int main()
{
	Solution s;
	cout << s.isScramble("rgtae", "great") << endl;
	cout << s.isScramble("abbbcbaaccacaacc", "acaaaccabcabcbcb") << endl;
	return 0;
}
