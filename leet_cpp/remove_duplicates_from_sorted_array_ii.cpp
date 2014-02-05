/*
http://oj.leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
Fri Jan 24 19:38:19 EST 2014


Remove Duplicates from Sorted Array II

Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array A = [1,1,1,2,2,3],

Your function should return length = 5, and A is now [1,1,2,2,3].
*/

class Solution {
public:
	int removeDuplicates(int A[], int n) {
		if (n <= 2)
			return n;
		int i = 1;
		int j = 2;
		int m = 2;
		while (j < n) {
			if (A[j] != A[i] || A[j] != A[i-1]) {
				A[++i] = A[j];
				++m;
			}
			++j;
		}
		return m;
	}
};

int main() {
	return 0;
}
