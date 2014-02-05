/*
http://oj.leetcode.com/problems/climbing-stairs/
Thu Jan 30 02:12:44 EST 2014


Climbing Stairs

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct
ways can you climb to the top?
*/

#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
	int climbStairs(int n) {
		assert(n > 0);
		int g = 1;
		int f = 1;
		int k = 1;
		while (k < n) {
			int h = g + f;
			g = f;
			f = h;
			++k;
		}
		return f;
	}
};

int main()
{
        return 0;
}
