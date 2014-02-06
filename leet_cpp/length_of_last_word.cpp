/*
http://oj.leetcode.com/problems/length-of-last-word/
Thu Feb  6 17:54:35 EST 2014


Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space
characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space
characters only.

For example,
Given s = "Hello World",
return 5.
*/

#include <iostream>

using namespace std;

class Solution {
public:
	int lengthOfLastWord(const char *s) {
		if (s == nullptr)
			return 0;
		int n_last = 0;
		int n = 0;
		while (*s) {
			if (isspace(*s)) {
				n = 0;
			}
			else {
				++n;
				n_last = n;
			}
			++s;
		}
		return n_last;
	}
};

int main()
{
        return 0;
}
