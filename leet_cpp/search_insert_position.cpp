/*
http://oj.leetcode.com/problems/search-insert-position/
Thu Feb 13 01:15:42 EST 2014


Search Insert Position

Given a sorted array and a target value, return the index if the
target is found. If not, return the index where it would be if it
were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/

class Solution {
public:
	int searchInsert(int A[], int n, int target) {
		int start = 0;
		int end = n;
		while (start < end) {
			int m = start + (end-start)/2;
			if (A[m] == target)
				return m;
			if (A[m] < target)
				start = m+1;
			else
				end = m;
		}
		return start;
	}
};

int main() {
	return 0;
}
