/*
http://oj.leetcode.com/problems/n-queens-ii/
Sat Feb  8 22:40:50 EST 2014


N-Queens II

Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total
number of distinct solutions.
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
	int total;

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
			++total;
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

public:
	int totalNQueens(int n) {
		sv.resize(n, -1);
		this->n = n;
		total = 0;
		if (n <= 0)
			return total;
		for (int col = 0; col < n; ++col) {
			sv[0] = col;
			solve(1);
		}
		return total;
	}
};

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	Solution s;
	cout << s.totalNQueens(atoi(argv[1])) << endl;
        return 0;
}
