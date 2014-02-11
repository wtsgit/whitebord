/*
http://oj.leetcode.com/problems/wildcard-matching/
Mon Feb 10 21:17:25 EST 2014


Wildcard Matching

Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

#include <iostream>

using namespace std;

class Solution {
public:
	bool isMatch(const char *s, const char *p) {

		if (s == nullptr || p == nullptr)
			return false;

		bool after_star = false;
		while (true) {
			while (*p && *p == '*') {
				++p;
				after_star = true;
			}
			if (after_star && !*p)
				return true;
			const char *ps = s;
			const char *pp = p;
			while (*ps && *pp && *pp != '*' && (*ps == *pp || *pp == '?')) {
				++ps;
				++pp;
			}
			if (*pp == '*') {
				p = pp;
				s = ps;
				continue;
			}
			if (!*pp) {
				if (!*ps)
					return true;
				if (!after_star)
					break;
			}
			else if (!*ps || !after_star) {
				break;
			}
			++s;
		}
		return false;
	}
};

int main() {
	Solution s;
	cout << s.isMatch("aa","a") << endl;
	cout << s.isMatch("aa","aa") << endl;
	cout << s.isMatch("aaa","aa") << endl;
	cout << s.isMatch("aa", "*") << endl;
	cout << s.isMatch("aa", "a*") << endl;
	cout << s.isMatch("ab", "?*") << endl;
	cout << s.isMatch("aab", "c*a*b") << endl;
#if 0
	cout << s.isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******************b") << endl;
	cout << s.isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******************ba") << endl;
	cout << s.isMatch("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb") << endl;
	cout << s.isMatch("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaacaaababaaaabb", "*c*") << endl;
#endif
	return 0;
}
