/*
http://oj.leetcode.com/problems/valid-parentheses/
Mon Jan 27 22:22:13 EST 2014


Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}',
'[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are
all valid but "(]" and "([)]" are not.
*/

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
	bool isValid(string s) {
		stack<char> st;
		for (auto const c : s) {
			switch (c) {
			case '(':
			case '{':
			case '[':
				st.push(c);
				break;
			case ')':
				if (!st.empty() && st.top() == '(') {
					st.pop();
					break;
				}
				return false;
			case '}':
				if (!st.empty() && st.top() == '{') {
					st.pop();
					break;
				}
				return false;
			case ']':
				if (!st.empty() && st.top() == '[') {
					st.pop();
					break;
				}
				return false;
			}
		}
		return st.empty();
	}
};

int main() {
	return 0;
}
