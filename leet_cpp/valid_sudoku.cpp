/*
http://oj.leetcode.com/problems/valid-sudoku/
Tue Feb 11 23:30:53 EST 2014


Valid Sudoku

Determine if a Sudoku is valid, according to: Sudoku Puzzles - The
Rules.

The Sudoku board could be partially filled, where empty cells are
filled with the character '.'.


A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable.
Only the filled cells need to be validated.
*/

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	bool isValidSudoku(vector<vector<char> > &board) {
		assert(board.size() == 9);
		assert(board[0].size() == 9);
		for (size_t i = 0; i < 9; ++i) {
			vector<bool> vb(9);
			for (size_t j = 0; j < 9; ++j) {
				if (board[i][j] == '.')
					continue;
				if (vb[board[i][j]-'1'])
					return false;
				vb[board[i][j]-'1'] = true;
			}
		}
		for (size_t i = 0; i < 9; ++i) {
			vector<bool> vb(9);
			for (size_t j = 0; j < 9; ++j) {
				if (board[j][i] == '.')
					continue;
				if (vb[board[j][i]-'1'])
					return false;
				vb[board[j][i]-'1'] = true;
			}
		}
		for (size_t i : {0,3,6}) {
			for (size_t j : {0,3,6}) {
				vector<bool> vb(9);
				for (size_t ii = i; ii < i+3; ++ii) {
					for (size_t jj = j; jj < j+3; ++jj) {
						if (board[ii][jj] == '.')
							continue;
						if (vb[board[ii][jj]-'1'])
							return false;
						vb[board[ii][jj]-'1'] = true;
					}
				}
			}
		}
		return true;
	}
};

int main() {
        return 0;
}
