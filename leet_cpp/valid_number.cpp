/*
http://oj.leetcode.com/problems/valid-number/
Mon Feb  3 17:23:04 EST 2014


Valid Number

Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

Note: It is intended for the problem statement to be ambiguous. You
should gather all requirements up front before implementing one.
*/

#include <iostream>

using namespace std;

class Solution {
public:
	bool isNumber(const char *s) {
		if (!s)
			return false;
		while (isspace(*s))
			++s;
		if (*s == '+' || *s == '-')
			++s;
		if (!isdigit(*s) && *s != '.')
			return false;
		bool has_mantissa = false;
		while (isdigit(*s)) {
			++s;
			has_mantissa = true;
		}
		if (*s == '.') {
			++s;
			while (isdigit(*s)) {
				has_mantissa = true;
				++s;
			}
		}
		if (!has_mantissa)
			return false;
		if (*s == 'e' || *s == 'E') {
			++s;
			if (*s == '+' || *s == '-')
				++s;
			if (!isdigit(*s))
				return false;
			while (isdigit(*s))
				++s;
		}
		while (isspace(*s))
			++s;
		return !*s;
	}
};

int main()
{
        return 0;
}
