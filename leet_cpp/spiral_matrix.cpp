/*
http://oj.leetcode.com/problems/spiral-matrix/
Thu Feb  6 17:08:45 EST 2014


Spiral Matrix

Given a matrix of m x n elements (m rows, n columns), return all elements
of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

You should return [1,2,3,6,9,8,7,4,5].
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> spiralOrder(vector<vector<int> > &matrix) {
		vector<int> r;

		if (matrix.size() == 0 || matrix[0].size() == 0)
			return r;

		size_t row_start = 0;
		size_t row_end = matrix.size();
		size_t col_start = 0;
		size_t col_end = matrix[0].size();
		enum {T=0, R=1, B=2, L=3};
		int edge = T;
		while (row_start < row_end && col_start < col_end) {
			switch (edge) {
			case T:
				for (size_t i = col_start; i < col_end; ++i)
					r.push_back(matrix[row_start][i]);
				++row_start;
				break;
			case R:
				for (size_t i = row_start; i < row_end; ++i)
					r.push_back(matrix[i][col_end-1]);
				--col_end;
				break;
			case B:
				for (size_t i = col_end; i > col_start; --i)
					r.push_back(matrix[row_end-1][i-1]);
				--row_end;
				break;
			case L:
				for (size_t i = row_end; i > row_start; --i)
					r.push_back(matrix[i-1][col_start]);
				++col_start;
			}
			edge = (edge+1) % 4;
		}
		return r;
	}
};

int main()
{
	vector<vector<int>> m = { { 1, 2, 3 },
				  { 4, 5, 6 },
				  { 7, 8, 9 } };
	Solution s;

	auto r = s.spiralOrder(m);
	for (auto x : r)
		cout << x << endl;

        return 0;
}
