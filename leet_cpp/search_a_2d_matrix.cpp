/*
http://oj.leetcode.com/problems/search-a-2d-matrix/
Fri Jan 31 14:15:06 EST 2014


Search a 2D Matrix

Write an efficient algorithm that searches for a value in an m x n
matrix. This matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer
    of the previous row.

For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

Given target = 3, return true.
*/

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <class T>
struct Accessor {
	const vector<vector<T>> &matrix;
	const size_t matrix_size;
	Accessor(const vector<vector<T>> &matrix) : matrix(matrix) , matrix_size(calculate_size()) {}
	size_t calculate_size() const {
		if (matrix.size() == 0)
			return 0;
		return matrix.size() * matrix[0].size();
	}
	size_t size() const {
		return matrix_size;
	}
	const T& operator[] (const size_t i) const {
		if (i >= matrix_size)
			throw std::out_of_range("Index out of range.");
		size_t row = i / matrix[0].size();
		size_t col = i % matrix[0].size();
		return matrix[row][col];
	}
};

class Solution {
public:
	bool binarySearch(const Accessor<int> &acc, int target) {
		size_t start = 0;
		size_t end = acc.size();
		while (start != end) {
			size_t m = start + (end-start)/2;
			if (acc[m] == target)
				return true;
			else if (acc[m] > target)
				end = m;
			else
				start = m+1;
		}
		return false;
	}

	bool searchMatrix(vector<vector<int> > &matrix, int target) {
		Accessor<int> acc(matrix);
		return binarySearch(acc, target);
	}
};

int main()
{
	vector<vector<int>> M = { {1,   3,  5,  7},
				  {10, 11, 16, 20},
				  {23, 30, 34, 50} };
	Solution s;
	cout << s.searchMatrix(M, 16) << endl;
        return 0;
}
