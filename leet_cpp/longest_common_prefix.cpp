/*
http://oj.leetcode.com/problems/longest-common-prefix/
Fri Jan 24 22:17:27 EST 2014


Longest Common Prefix

Write a function to find the longest common prefix string amongst
an array of strings.
*/

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	string longestCommonPrefix(vector<string> &strs) {
		string prefix;
		if (strs.size() == 0)
			return prefix;
		for (size_t i = 0; i < strs[0].size(); ++i) {
			auto c = strs[0][i];
			for (auto const &s : strs) {
				if (i >= s.size() || c != s[i]) {
					return prefix;
				}
			}
			prefix.push_back(c);
		}
		return prefix;
	}
};

int main() {
	return 0;
}
