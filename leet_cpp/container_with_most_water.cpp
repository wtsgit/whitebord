/*
http://oj.leetcode.com/problems/container-with-most-water/
Sun Feb 16 18:58:47 EST 2014


Container With Most Water

Given n non-negative integers a1, a2, ..., an, where each represents
a point at coordinate (i, ai). n vertical lines are drawn such that
the two endpoints of line i is at (i, ai) and (i, 0). Find two
lines, which together with x-axis forms a container, such that the
container contains the most water.

Note: You may not slant the container.
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	int maxArea(vector<int> &height) {
		if (height.size() == 0)
			return 0;
		size_t l = 0;
		size_t h = height.size()-1;
		int cap = 0;
		while (l < h) {
			cap = max(cap, (int)(h-l) * min(height[l], height[h]));
			if (height[l] < height[h])
				++l;
			else
				--h;
		}
		return cap;
	}
};

int main() {
	return 0;
}
