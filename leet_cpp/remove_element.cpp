/*
http://oj.leetcode.com/problems/remove-element/
Wed Jan 29 03:16:30 EST 2014


Remove Element

Given an array and a value, remove all instances of that value in
place and return the new length.

The order of elements can be changed. It doesn't matter what you
leave beyond the new length.
*/

class Solution {
public:
	int removeElement(int A[], int n, int elem) {
		int nn = 0;
		int i = 0;
		int j = 0;
		while (j < n) {
			while (j < n && A[j] == elem)
				++j;
			while (j < n && A[j] != elem) {
				A[i++] = A[j++];
				++nn;
			}
		}
		return nn;
	}
};

int main() {
	return 0;
}
