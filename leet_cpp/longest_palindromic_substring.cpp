/*
http://oj.leetcode.com/problems/longest-palindromic-substring/
Mon Feb 17 19:45:45 EST 2014


Longest Palindromic Substring

Given a string S, find the longest palindromic substring in S. You
may assume that the maximum length of S is 1000, and there exists
one unique longest palindromic substring.
*/

#include <string>

using namespace std;

class Solution {
private:
	pair<size_t, size_t> expand_palindrome(const string &s, size_t i, size_t j) {
		size_t start = 0;
		size_t end = 0;
		while (s[i] == s[j]) {
			start = i;
			end = j+1;
			if (i == 0 || j+1 == s.size())
				break;
			--i;
			++j;
		}
		return {start, end};
	}
public:
	string longestPalindrome(string s) {
		pair<size_t, size_t> longest{};
		size_t maxlen = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			auto p = expand_palindrome(s, i, i);
			if (p.second - p.first > maxlen) {
				longest = p;
				maxlen = p.second - p.first;
			}
			if (i+1 < s.size()) {
				auto p = expand_palindrome(s, i, i+1);
				if (p.second - p.first > maxlen) {
					longest = p;
					maxlen = p.second - p.first;
				}
			}
		}
		return s.substr(longest.first, maxlen);
	}
};

int main() {
	return 0;
}
