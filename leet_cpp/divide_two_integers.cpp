/*
http://oj.leetcode.com/problems/divide-two-integers/
Fri Feb 14 17:42:31 EST 2014


Divide Two Integers

Divide two integers without using multiplication, division and mod
operator.
*/

#include <iostream>
#include <climits>
#include <cstdlib>

using namespace std;

class Solution {
public:
	int divide(int dividend, int divisor) {
		bool positive = true;
		unsigned a = dividend;
		if (dividend < 0) {
			a = -dividend;
			positive = !positive;
		}
		unsigned b = divisor;
		if (divisor < 0) {
			b = -divisor;
			positive = !positive;
		}

		if (divisor == 0) {
			if (dividend == 0)
				return 0;
			if (positive)
				return INT_MAX;
			return INT_MIN;
		}

		unsigned int msb = 1;
		while ((msb << 1))
			msb <<= 1;

		unsigned q = 0;
		unsigned mask = 1;
		while (b < a && (b & msb) == 0) {
			b <<= 1;
			mask <<= 1;
		}
		while (mask) {
			if (a >= b) {
				a -= b;
				q |= mask;
			}
			b >>= 1;
			mask >>= 1;
		}
		if (positive && q > (unsigned int)INT_MAX)
			return INT_MAX;
		if (!positive)
			return -(int)q;
		return (int)q;
	}
};

int main(int argc, char **argv) {
	if (argc < 3)
		return 1;

	Solution s;
	cout << s.divide(atoi(argv[1]), atoi(argv[2])) << endl;

	return 0;
}
