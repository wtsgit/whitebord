/*
http://oj.leetcode.com/problems/trapping-rain-water/
Tue Feb 11 20:10:05 EST 2014


Trapping Rain Water

Given n non-negative integers representing an elevation map where
the width of each bar is 1, compute how much water it is able to
trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
In this case, 6 units of rain water (blue section) are being trapped.
*/

#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
	int trap(int A[], int n) {
		stack<size_t> st;
		int water = 0;
		for (size_t i = 0; i < (size_t)n; ++i) {
			while (!st.empty() && A[i] >= A[st.top()]) {
				size_t t = st.top(); st.pop();
				if (!st.empty()) {
					water += (i - st.top() - 1) * (min(A[i], A[st.top()]) - A[t]);
				}
			}
			st.push(i);
		}
		return water;
	}
};

int main() {
	{
	int A[] = {0,1,0,2,1,0,1,3,2,1,2,1};
	size_t n = sizeof(A)/sizeof(*A);
	Solution s;
	cout << s.trap(A, n) << endl;
	}
	{
	int A[] = {0,1,0,2};
	size_t n = sizeof(A)/sizeof(*A);
	Solution s;
	cout << s.trap(A, n) << endl;
	}
	return 0;
}
