/*
http://oj.leetcode.com/problems/sqrtx/
Fri Jan 31 21:39:47 EST 2014


Sqrt(x)

Implement int sqrt(int x).

Compute and return the square root of x.
*/

#include <iostream>

using namespace std;

class Solution {
public:
	int sqrt(int x) {
		if (x == 0)
			return 0;
		int start = 1;
		int end = x/2+1;
		while (start < end) {
			int r = start + (end-start)/2;
			int q1 = x/r;
			int q2 = x/(r+1);
			if (q1 >= r && q2 < r+1)
				return r;
			if (q1 < r)
				end = r;
			if (q2 >= r+1)
				start = r+1;
		}
		return start;
	}
};

int main()
{
	Solution s;
	for (int i = 0; i <= 100; ++i)
		cout << i << ": " << s.sqrt(i) << endl;
	cout << 2147395599 << ": " << s.sqrt(2147395599) << endl;
        return 0;
}
