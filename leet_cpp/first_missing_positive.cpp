/*
http://oj.leetcode.com/problems/first-missing-positive/
Sun Feb  9 01:03:32 EST 2014


First Missing Positive

Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/

#include <iostream>

using namespace std;

class Solution {
public:
	int firstMissingPositive(int A[], int n) {
		for (int i = 1; i <= n; ++i) {
			int j = A[i-1];
			while (j >= 1 && j <= n && j != i && A[i-1] != A[j-1]) {
				swap(A[i-1], A[j-1]);
				j = A[i-1];
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (A[i-1] != i)
				return i;
		}
		return n+1;
	}
};

int main()
{
	Solution s;
	{
		int A[] = {1, 2, 0};
		cout << s.firstMissingPositive(A, 3);
		cout << endl;
	}
	{
		int A[] = {3, 4, -1, 1};
		cout << s.firstMissingPositive(A, 4);
		cout << endl;
	}
	{
		int A[] = {1, 1};
		cout << s.firstMissingPositive(A, 2);
		cout << endl;
	}
        return 0;
}
