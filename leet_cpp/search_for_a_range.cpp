/*
http://oj.leetcode.com/problems/search-for-a-range/
Wed Jan 29 03:35:35 EST 2014


Search for a Range

Given a sorted array of integers, find the starting and ending
position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/

#include <vector>

using namespace std;

class Solution {
public:
	vector<int> searchRange(int A[], int n, int target) {
		int low = -1;
		int high = -1;
		int start = 0;
		int end = n;
		while (start != end) {
			int mid = start + (end-start)/2;
			if (A[mid] == target) {
				low = mid;
				end = mid;
			}
			else if (A[mid] > target) {
				end = mid;
			}
			else {
				start = mid+1;
			}
		}
		if (low == -1) {
			return {-1, -1};
		}
		start = 0;
		end = n;
		while (start != end) {
			int mid = start + (end-start)/2;
			if (A[mid] == target) {
				high = mid;
				start = mid+1;
			}
			else if (A[mid] > target) {
				end = mid;
			}
			else {
				start = mid+1;
			}
		}
		return {low, high};
	}
};

int main() {
	return 0;
}
