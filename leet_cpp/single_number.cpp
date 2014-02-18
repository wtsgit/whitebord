/*
http://oj.leetcode.com/problems/single-number/
Mon Feb 17 20:17:44 EST 2014


Single Number

Given an array of integers, every element appears twice except for
one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you
implement it without using extra memory?
*/

class Solution {
public:
	int singleNumber(int A[], int n) {
		int k = 0;
		for (int i = 0; i < n; ++i) {
			k ^= A[i];
		}
		return k;
	}
};

int main() {
	return 0;
}
