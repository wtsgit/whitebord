/*
http://oj.leetcode.com/problems/implement-strstr/
Fri Feb 14 18:40:35 EST 2014


Implement strStr()

Returns a pointer to the first occurrence of needle in haystack,
or null if needle is not part of haystack.
*/

#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
	char *strStr(char *haystack, char *needle) {
		assert(haystack);
		assert(needle);
		if (!*needle) {
			return haystack;
		}
		while (*haystack) {
			char *p = haystack;
			char *q = needle;
			while (*p && *q && *p == *q) {
				++p;
				++q;
			}
			if (!*q)
				return haystack;
			if (!*p)
				return nullptr;
			++haystack;
		}
		return nullptr;
	}
};

int main(int argc, char **argv) {
	if (argc < 3)
		return 1;
	Solution s;
	char *p = s.strStr(argv[1], argv[2]);
	if (p)
		cout << p << endl;
	else
		cout << "(null)" << endl;
	return 0;
}
