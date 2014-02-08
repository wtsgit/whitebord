/*
http://oj.leetcode.com/problems/maximum-subarray/
Sat Feb  8 18:31:08 EST 2014


Maximum Subarray

Find the contiguous subarray within an array (containing at least
one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

More practice:

If you have figured out the O(n) solution, try coding another
solution using the divide and conquer approach, which is more subtle.
*/

#include <iostream>

using namespace std;

class Solution {
public:
	int maxSubArray(int A[], int n) {
		if (n <= 0)
			return 0;
		int m = A[0];
		int m_until = A[0];
		for (size_t i = 1; i < n; ++i) {
			if (m_until <= 0) {
				m_until = A[i];
			}
			else {
				m_until += A[i];
			}
			if (m_until > m) {
				m = m_until;
			}
		}
		return m;
	}
};

int main()
{
        return 0;
}

