/*
http://oj.leetcode.com/problems/spiral-matrix/
Thu Feb  6 17:20:00 EST 2014


Spiral Matrix II

Given an integer n, generate a square matrix filled with elements from
1 to n2 in spiral order.

For example,
Given n = 3,
You should return the following matrix:

[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Solution {
public:
	vector<vector<int> > generateMatrix(int n) {
		vector<vector<int>> matrix;
		if (n <= 0)
			return matrix;
		matrix.resize(n);
		for (size_t i = 0; i < matrix.size(); ++i)
			matrix[i].resize(n);

		size_t row_start = 0;
		size_t row_end = matrix.size();
		size_t col_start = 0;
		size_t col_end = matrix[0].size();
		enum {T=0, R=1, B=2, L=3};
		int edge = T;
		int k = 1;
		while (row_start < row_end && col_start < col_end) {
			switch (edge) {
			case T:
				for (size_t i = col_start; i < col_end; ++i) {
					matrix[row_start][i] = k++;
				}
				++row_start;
				break;
			case R:
				for (size_t i = row_start; i < row_end; ++i) {
					matrix[i][col_end-1] = k++;
				}
				--col_end;
				break;
			case B:
				for (size_t i = col_end; i > col_start; --i) {
					matrix[row_end-1][i-1] = k++;
				}
				--row_end;
				break;
			case L:
				for (size_t i = row_end; i > row_start; --i) {
					matrix[i-1][col_start] = k++;
				}
				++col_start;
			}
			edge = (edge+1) % 4;
		}
		return matrix;
	}
};

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	Solution s;
	auto r = s.generateMatrix(atoi(argv[1]));
	for (auto x : r) {
		for (auto y : x)
			cout << y << " ";
		cout << endl;
	}
        return 0;
}
