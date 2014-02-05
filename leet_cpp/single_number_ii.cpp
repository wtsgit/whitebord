/*
http://oj.leetcode.com/problems/single-number-ii/
Fri Jan 31 15:18:36 EST 2014


Single Number II

Given an array of integers, every element appears three times except
for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you
implement it without using extra memory?
*/

#include <iostream>

using namespace std;

class Solution {
public:
	int singleNumber(int A[], int n) {
		constexpr size_t nbits = sizeof(int) * 8;
		size_t sum[nbits]{};
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < nbits; ++k) {
				if (A[i] & (1<<k))
					++sum[k];
			}
		}
		int result = 0;
		for (int k = 0; k < nbits; ++k) {
			if ((sum[k] %= 3))
				result |= (1<<k);
		}
		return result;
	}
};

int main()
{
	int A[] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8};
	Solution s;
	cout << s.singleNumber(A, sizeof(A)/sizeof(int)) << endl;
        return 0;
}
