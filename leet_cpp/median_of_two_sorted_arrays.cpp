/*
http://oj.leetcode.com/problems/median-of-two-sorted-arrays/
Mon Feb 17 17:30:26 EST 2014


Median of Two Sorted Arrays

There are two sorted arrays A and B of size m and n respectively.
Find the median of the two sorted arrays. The overall run time
complexity should be O(log (m+n)).
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
private:
	int find_kth(int *start_a, int *end_a, int *start_b, int *end_b, size_t k) {
		while (start_a < end_a && start_b < end_b) {
			int *mid_b = start_b + (end_b-start_b)/2;
			int *lb_mid_b_in_a = lower_bound(start_a, end_a, *mid_b);
			size_t rank_of_mid_b_in_merged = (lb_mid_b_in_a - start_a) + (mid_b - start_b) + 1;
			if (rank_of_mid_b_in_merged == k)
				return *mid_b;
			if (rank_of_mid_b_in_merged > k) {
				end_a = lb_mid_b_in_a;
				end_b = mid_b;
			}
			else {
				start_a = lb_mid_b_in_a;
				start_b = mid_b+1;
				k -= rank_of_mid_b_in_merged;
			}
		}
		if (start_a < end_a)
			return *(start_a + k-1);
		return *(start_b + k-1);
	}
public:
	double findMedianSortedArrays(int A[], int m, int B[], int n) {
		if ((m+n) & 1) {
			// odd
			return (double)find_kth(A, A+m, B, B+n, (m+n)/2+1);
		}
		double m1 = (double)find_kth(A, A+m, B, B+n, (m+n)/2);
		double m2 = (double)find_kth(A, A+m, B, B+n, (m+n)/2+1);
		return (m1+m2)/2;
	}
};

int main() {
	int A[] = {};
	int B[] = {2, 3};
	Solution s;
	cout << s.findMedianSortedArrays(A, 0, B, 2) << endl;
	return 0;
}
