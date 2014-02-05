/*
http://oj.leetcode.com/problems/string-to-integer-atoi/
Fri Jan 24 20:18:58 EST 2014


String to Integer (atoi)

Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a
challenge, please do not see below and ask yourself what are the
possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie,
no given input specs). You are responsible to gather all the input
requirements up front.

spoilers alert... click to show requirements for atoi.
Requirements for atoi:

The function first discards as many whitespace characters as necessary
until the first non-whitespace character is found. Then, starting
from this character, takes an optional initial plus or minus sign
followed by as many numerical digits as possible, and interprets
them as a numerical value.

The string can contain additional characters after those that form
the integral number, which are ignored and have no effect on the
behavior of this function.

If the first sequence of non-whitespace characters in str is not a
valid integral number, or if no such sequence exists because either
str is empty or it contains only whitespace characters, no conversion
is performed.

If no valid conversion could be performed, a zero value is returned.
If the correct value is out of the range of representable values,
INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
*/

#include <iostream>
#include <cctype>
#include <climits>

using namespace std;

class Solution {
public:
	int atoi(const char *str) {
		while (isspace(*str))
			++str;
		bool isPositive = true;
		if (*str == '-') {
			isPositive = false;
			++str;
		}
		else if (*str == '+') {
			++str;
		}
		else if (!isdigit(*str)) {
			return 0;
		}
		int n = 0;
		while (isdigit(*str)) {
			if (n < INT_MIN/10) {
				n = INT_MIN;
				break;
			}
			n *= 10;
			if ('0' - *str < INT_MIN - n) {
				n = INT_MIN;
				break;
			}
			n += '0' - *str;
			++str;
		}

		if (isPositive) {
			if (n == INT_MIN)
				n = INT_MAX;
			else
				n = -n;
		}

		return n;
	}
};

int main(int argc, char **argv) {
	if (argc < 2)
		return 1;
	Solution s;
	cout << s.atoi(argv[1]) << endl;
	return 0;
}
