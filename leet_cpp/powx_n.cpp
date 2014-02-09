/*
http://oj.leetcode.com/problems/powx-n/
Sat Feb  8 23:04:35 EST 2014


Pow(x, n)

Implement pow(x, n).
*/

#include <iostream>
#include <cstdlib>

using namespace std;

class Solution {
public:
	double pow(double x, int n) {
		unsigned un = n;
		if (n < 0) {
			x = 1/x;
			if (n != INT_MIN)
				un = -n;
		}
		double p = 1;
		double p2 = x;
		while (un > 0) {
			if (un & 1)
				p *= p2;
			un >>= 1;
			p2 *= p2;
		}
		return p;
	}
};

int main(int argc, char **argv)
{
	int i = INT_MIN;
	cout << i+1 << endl;
	int j = i+1;
	j = -1;
	unsigned int u = j;
	cout << u << endl;
	Solution s;
	if (argc < 3)
		return 1;
	cout << s.pow(atof(argv[1]), atoi(argv[2])) << endl;
        return 0;
}
