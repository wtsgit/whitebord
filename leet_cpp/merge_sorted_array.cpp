/*
http://oj.leetcode.com/problems/merge-sorted-array/
Wed Jan 22 18:07:50 EST 2014


Merge Sorted Array

Given two sorted integer arrays A and B, merge B into A as one sorted array.

Note:
You may assume that A has enough space to hold additional elements
from B. The number of elements initialized in A and B are m and n
respectively.
*/

#include <iostream>

using namespace std;

class Solution {
public:
	void merge(int A[], int m, int B[], int n) {
		for (size_t i = m+n; i > n; --i) {
			A[i-1] = A[i-1-n];
		}
		int *a = A+n;
		int *ae = A+m+n;
		int *b = B;
		int *be = B+n;
		int *result = A;
		while (a != ae && b != be) {
			if (*a < *b)
				*result++ = *a++;
			else
				*result++ = *b++;
		}
		while (a != ae)
			*result++ = *a++;
		while (b != be)
			*result++ = *b++;
	}
};

int main()
{
	return 0;
}
