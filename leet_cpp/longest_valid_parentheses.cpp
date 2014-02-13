/*
http://oj.leetcode.com/problems/longest-valid-parentheses/
Thu Feb 13 14:49:24 EST 2014


Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the
length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which
has length = 2.

Another example is ")()())", where the longest valid parentheses
substring is "()()", which has length = 4.
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
	int longestValidParentheses(string s) {
		stack<pair<char, size_t>> st;
		st.emplace(')', 0);
		size_t maxlen = 0;
		for (auto c : s) {
			if (c == ')') {
				auto ch = st.top().first;
				if (ch == '(') {
					auto n = st.top().second;
					st.pop();
					st.top().second += n+2;
					if (st.top().second > maxlen)
						maxlen = st.top().second;
					continue;
				}  
			}
			st.emplace(c, 0);
		}
		return (int)maxlen;
	}
};

int main() {
	return 0;
}
