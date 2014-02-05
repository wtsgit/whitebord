/*
http://oj.leetcode.com/problems/search-in-rotated-sorted-array-ii/
Sat Feb  1 16:45:00 EST 2014


Search in Rotated Sorted Array II

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/

#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
	bool search(int A[], int n, int target) {
		size_t start = 0;
		size_t end = n;
		stack<pair<size_t, size_t>> s;
		while (start < end || !s.empty()) {
			if (start == end) {
				start = s.top().first;
				end = s.top().second;
				s.pop();
			}

			size_t m = start + (end-start)/2;

			// [start, m), [m, m+1), [m+1, end)
			if (A[m] == target) {
				return true;
			}
			if (start == m) {
				start = m+1;
				continue;
			}
			if (m+1 == end) {
				end = m;
				continue;
			}

			bool left_not_rotated = false;
			bool right_not_rotated = false;

			if (A[start] < A[m-1])
				left_not_rotated = true;
			else if (A[start] > A[m-1])
				right_not_rotated = true;

			if (A[m+1] < A[end-1])
				right_not_rotated = true;
			else if (A[m+1] > A[end-1])
				left_not_rotated = true;

			if (left_not_rotated) {
				if (target >= A[start] && target <= A[m-1])
					end = m;
				else
					start = m+1;
			}
			else if (right_not_rotated) {
				if (target >= A[m+1] && target <= A[end-1])
					start = m+1;
				else
					end = m;
			}
			else {
				s.emplace(start, m);
				start = m+1;
			}
		}
		return false;
	}
};

int main()
{
	int A[] = {4, 4, 5, 5, 6, 7, 8, 9, 10, 10, 11, 11, 12, 12, -1, -1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 4, 4, 4, 4};
	constexpr size_t n = sizeof(A)/sizeof(*A);
	Solution s;
	cout << s.search(A, n, 1) << endl;
	cout << A[s.search(A, n, 1)] << endl;
        return 0;
}

