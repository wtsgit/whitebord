/*
http://oj.leetcode.com/problems/set-matrix-zeroes/
Sat Feb 1 23:30:08 EST 2014


Set Matrix Zeroes

Given a m x n matrix, if an element is 0, set its entire row and
column to 0. Do it in place.

click to show follow up.
Follow up:

Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	void setZeroes(vector<vector<int> > &matrix) {
		const size_t m = matrix.size();
		if (m == 0)
			return;
		const size_t n = matrix[0].size();
		if (n == 0)
			return;
		bool zero_last_row = false;
		for (auto x : matrix[0]) {
			if (x == 0) {
				zero_last_row = true;
				break;
			}
		}
		for (size_t i = 1; i < m; ++i) {
			bool zero_row = false;
			for (size_t j = 0; j < n; ++j) {
				if (matrix[i][j] == 0)
					zero_row = true;
				if (matrix[i-1][j] == 0)
					matrix[i][j] = 0;
			}
			if (zero_last_row) {
				for (auto &x : matrix[i-1])
					x = 0;
			}
			zero_last_row = zero_row;
		}
		for (size_t j = 0; j < n; ++j) {
			if (matrix[m-1][j] == 0) {
				for (size_t i = 0; i < matrix.size(); ++i)
					matrix[i][j] = 0;
			}
		}
		if (zero_last_row) {
			for (auto &x : matrix[m-1])
				x = 0;
		}
	}
};

int main()
{
	vector<vector<int>> vvi = { {1, 1, 0, 1},
				    {2, 2, 1, 1},
				    {1, 0, 2, 0},
				    {1, 2, 3, 4} };
	Solution s;
	for (const auto &row : vvi) {
		for (auto i : row)
			cout << i << " ";
		cout << endl;
	}
	cout << endl;
	s.setZeroes(vvi);
	for (const auto &row : vvi) {
		for (auto i : row)
			cout << i << " ";
		cout << endl;
	}
        return 0;
}
