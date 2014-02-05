/*
http://oj.leetcode.com/problems/largest-rectangle-in-histogram/
Tue Jan 28 21:46:37 EST 2014


Largest Rectangle in Histogram

Given n non-negative integers representing the histogram's bar
height where the width of each bar is 1, find the area of largest
rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given height = [2,1,5,6,2,3],
return 10.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
	int largestRectangleArea(vector<int> &height) {
		stack<size_t> s;
		int m = 0;
		s.push(0);
		size_t i = 1;
		// height: [0 .. height.size()-1]
		//       [0,1 .. height.size(),  height.size()+1]
		//        0                      0
		while (i <= height.size()+1) {
			int x = (i < height.size()+1) ? height[i-1] : 0;
			int y = (s.top() == 0) ? 0 : height[s.top()-1];
			if (x >= y) {
				s.push(i);
				++i;
			}
			else {
				int t = s.top();
				s.pop();
				m = std::max(m, (int)(i - s.top()-1) * height[t-1]);
			}
		}
		return m;
	}
};

int main()
{
	Solution s;
	vector<int> h{6, 6, 6, 6, 6, 1};
	cout << s.largestRectangleArea(h) << endl;
	h = {2, 1, 5, 6, 2, 3};
	cout << s.largestRectangleArea(h) << endl;
	return 0;
}
