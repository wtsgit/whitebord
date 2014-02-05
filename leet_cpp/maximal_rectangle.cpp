/*
http://oj.leetcode.com/problems/maximal-rectangle/
Fri Jan 31 21:39:04 EST 2014


Maximal Rectangle

Given a 2D binary matrix filled with 0's and 1's, find the largest
rectangle containing all ones and return its area.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
	size_t maxHist(const vector<size_t> &v) {
		stack<size_t> s;
		size_t m = 0;
		for (size_t i = 0; i < v.size(); ++i) {
			while (!s.empty() && v[i] < v[s.top()]) {
				auto j = s.top();
				s.pop();
				m = max(m, v[j] * (s.empty() ? i : i-s.top()-1));
			}
			s.push(i);
		}
		return m;
	}
	int maximalRectangle(vector<vector<char> > &matrix) {
		if (matrix.size() == 0)
			return 0;
		vector<size_t> v(matrix[0].size()+1, 0);
		size_t m = 0;
		for (const auto &x : matrix) {
			for (size_t i = 0; i < x.size(); ++i) {
				if (x[i] == '1')
					++v[i];
				else
					v[i] = 0;
			}
			m = max(m, maxHist(v));
		}
		return (int)m;
	}
};

int main()
{
	vector<vector<char>> mat = { { '0', '0', '0', '0', '0', '0'},
				     { '0', '1', '1', '1', '1', '0'},
				     { '1', '1', '1', '1', '1', '0'},
				     { '0', '1', '1', '1', '1', '0'},
				     { '0', '0', '1', '1', '1', '0'},
				     { '0', '0', '1', '1', '1', '0'},
				     { '0', '0', '1', '1', '1', '0'},
				     { '0', '0', '1', '1', '1', '0'},
				     { '0', '0', '1', '1', '1', '0'},
				     { '0', '0', '1', '1', '1', '1'},
				     { '0', '0', '1', '1', '1', '0'},
				     { '0', '1', '1', '1', '1', '0'},
				     { '0', '1', '0', '0', '1', '0'},
				     { '1', '1', '1', '0', '1', '0'} };
	Solution s;
	cout << s.maximalRectangle(mat) << endl;
	mat = {{'1'}};
	cout << s.maximalRectangle(mat) << endl;
        return 0;
}
