/*
http://oj.leetcode.com/problems/regular-expression-matching/
Sun Feb 16 19:05:56 EST 2014


Regular Expression Matching

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

#include <iostream>

using namespace std;

class Solution {
public:
	bool isMatch(const char *s, const char *p) {
		while (*s && *p && *(p+1) != '*' && (*s == *p || *p == '.')) {
			++s;
			++p;
		}
		if (!*p)
			return !*s;
		if (*(p+1) != '*')
			return false;
		if (isMatch(s, p+2))
			return true;
		if (*p == '.' && *s)
			return isMatch(s+1, p);
		if (*p == *s)
			return isMatch(s+1, p);
		return false;
	}
};

int main() {
	Solution s;
	cout << s.isMatch("aa","a") << endl;
	cout << s.isMatch("aa","aa") << endl;
	cout << s.isMatch("aaa","aa") << endl;
	cout << s.isMatch("aa", "a*") << endl;
	cout << s.isMatch("aa", ".*") << endl;
	cout << s.isMatch("ab", ".*") << endl;
	cout << s.isMatch("aab", "c*a*b") << endl;
	return 0;
}
