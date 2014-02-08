/*
http://oj.leetcode.com/problems/jump-game/
Sat Feb  8 17:37:48 EST 2014


Jump Game

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	bool canJump(int A[], int n) {
		if (n <= 0)
			return false;
		if (n == 1)
			return true;
		vector<bool> jump(n, false);
		jump[n-1] = true;
		size_t lowest = n-1;
		for (size_t ip1 = n-1; ip1 > 0; --ip1) {
			size_t i = ip1-1;
			if (i+A[i] >= lowest) {
				jump[i] = true;
				lowest = i;
			}
		}
		return jump[0];
	}
};

int main()
{
	int A1[] = {2,3,1,1,4};
	int A2[] = {3,2,1,0,4};
	Solution s;
	cout << s.canJump(A1, 5) << endl;
	cout << s.canJump(A2, 5) << endl;
        return 0;
}
