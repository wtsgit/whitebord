/*
http://oj.leetcode.com/problems/n-queens/
Sat Feb  8 20:59:54 EST 2014


N-Queens

The n-queens puzzle is the problem of placing n queens on an n×n
chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens
puzzle.

Each solution contains a distinct board configuration of the n-queens'
placement, where 'Q' and '.' both indicate a queen and an empty
space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class Solution {
private:
	vector<int> sv;
	int n;
	vector<vector<string>> r;

private:
	bool feasible(int new_row, int new_col) {
		for (int row = 0; row < sv.size(); ++row) {
			if (sv[row] != -1) {
				int row_diff = abs(new_row-row);
				int col_diff = abs(new_col-sv[row]);
				if (row_diff == 0 || col_diff == 0 || row_diff == col_diff)
					return false;
			}
		}
		return true;
	}

	void solve(int row) {
		if (!(row < n)) {
			collect();
			return;
		}

		for (int col = 0; col < n; ++col) {
			if (feasible(row, col)) {
				sv[row] = col;
				solve(row+1);
				sv[row] = -1;
			}
		}
	}

	void collect() {
		vector<string> vs;
		for (int row = 0; row < n; ++row) {
			string s;
			for (int col = 0; col < n; ++col) {
				if (col != sv[row])
					s.push_back('.');
				else
					s.push_back('Q');
			}
			vs.push_back(s);
		}
		r.push_back(vs);
	}

public:
	vector<vector<string> > solveNQueens(int n) {
		sv.resize(n, -1);
		this->n = n;
		if (n <= 0)
			return r;
		for (int col = 0; col < n; ++col) {
			sv[0] = col;
			solve(1);
		}
		return r;
	}
};

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	Solution s;
	auto r = s.solveNQueens(atoi(argv[1]));
	for (auto u : r) {
		for (auto v : u) 
			cout << v << endl;
		cout << endl;
	}
        return 0;
}
