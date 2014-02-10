/*
http://oj.leetcode.com/problems/rotate-image/
Sun Feb  9 19:41:01 EST 2014


Rotate Image

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
*/

#include <vector>

using namespace std;

class Solution {
public:
	void rotate(vector<vector<int> > &matrix) {
		size_t rb = 0;
		size_t re = matrix.size();
		if (re == 0)
			return;
		size_t cb = 0;
		size_t ce = matrix[0].size();
		if (ce == 0)
			return;
		while (rb < re) {
			size_t n = re - rb;
			for (size_t i = 0; i < n-1; ++i) {
				auto a1 = matrix[rb][cb+i];
				auto a2 = matrix[rb+i][ce-1];
				auto a3 = matrix[re-1][ce-1-i];
				auto a4 = matrix[re-1-i][cb];

				matrix[rb+i][ce-1] = a1;
				matrix[re-1][ce-1-i] = a2;
				matrix[re-1-i][cb] = a3;
				matrix[rb][cb+i] = a4;
			}
			++rb; --re;
			++cb; --ce;
		}
		return;
	}
};

int main() {
	return 0;
}

