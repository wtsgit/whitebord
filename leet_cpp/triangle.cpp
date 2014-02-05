/*
http://oj.leetcode.com/problems/triangle/
Sun Jan 12 00:31:29 EST 2014


Triangle

Given a triangle, find the minimum path sum from top to bottom.
Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space,
where n is the total number of rows in the triangle.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int minimumTotal(vector<vector<int> > &triangle) {
		size_t n = triangle.size();
		if (n == 0)
			return 0;
		vector<int> v(triangle.back());
		for (size_t l = n-1; l >= 1; --l) {
			vector<int> &u = triangle[l-1];
			for (size_t i = 0; i < u.size(); ++i) {
				v[i] = u[i] + min(v[i], v[i+1]);
			}
		}
		return v[0];
	}
};

int main()
{
	vector<vector<int> > triangle;
	vector<int> vec;
	vec.push_back(2);
	triangle.push_back(vec);

	vec.clear();
	vec.push_back(3);
	vec.push_back(4);
	triangle.push_back(vec);

	vec.clear();
	vec.push_back(6);
	vec.push_back(5);
	vec.push_back(7);
	triangle.push_back(vec);

	vec.clear();
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(8);
	vec.push_back(3);
	triangle.push_back(vec);

	Solution s;
	cout << s.minimumTotal(triangle) << endl;

	return 0;
}
