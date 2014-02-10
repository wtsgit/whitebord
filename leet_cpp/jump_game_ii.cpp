/*
http://oj.leetcode.com/problems/jump-game-ii/
Mon Feb 10 16:09:38 EST 2014


Jump Game II

Given an array of non-negative integers, you are initially positioned
at the first index of the array.

Each element in the array represents your maximum jump length at
that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1
step from index 0 to 1, then 3 steps to the last index.)
*/
#include <iostream>

using namespace std;

class Solution {
public:
	int jump(int A[], int n) {
		int jump = 0;
		size_t zone_start = 0;
		size_t zone_end = 1;
		while (zone_end < n) {
			size_t new_end = zone_end;
			for (size_t i = zone_start; i < zone_end; ++i) {
				new_end = max(new_end, A[i]+i+1);
			}
			if (new_end == zone_end)
				return -1;
			zone_start = zone_end;
			zone_end = new_end;
			++jump;
		}
		return jump;
	}
};

int main() {
	int A[] = {2,3,1,1,4};
	Solution s;
	cout << s.jump(A, 5) << endl;
	return 0;
}
