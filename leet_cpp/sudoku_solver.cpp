#include <cassert>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
private:
	int get_row(int index) { return index/9; }
	int get_col(int index) { return index%9; }

	bool feasible(const vector<vector<char> > &board, int index, char c) {
		int row = get_row(index);
		int col = get_col(index);
		for (int i = 0; i < 9; ++i)
			if (board[i][col] == c)
				return false;
		for (int j = 0; j < 9; ++j)
			if (board[row][j] == c)
				return false;
		int block_row = (row / 3) * 3;
		int block_col = (col / 3) * 3;
		for (int i = block_row; i < block_row+3; ++i)
			for (int j = block_col; j < block_col+3; ++j)
				if (board[i][j] == c)
					return false;
		return true;
	}

public:
	void solveSudoku(vector<vector<char> > &board) {
		assert(board.size() == 9);
		for (const auto &row : board)
			assert(row.size() == 9);

		vector<int> indices;
		for (int i = 0; i < 9*9; ++i)
			if (board[get_row(i)][get_col(i)] == '.')
				indices.push_back(i);

		stack<pair<int, char>> st;
		st.emplace(0, '1');
		while (!st.empty()) {
			int seq = st.top().first;
			char &choice = st.top().second;
			if (!(seq < indices.size()))
				return;
			int index = indices[seq];
			while (choice <= '9' && !feasible(board, index, choice))
				++choice;
			if (choice > '9') {
				board[get_row(index)][get_col(index)] = '.';
				st.pop();
				continue;
			}
			board[get_row(index)][get_col(index)] = choice;
			st.emplace(seq+1, '1');
		}
	}
};

int main()
{
	vector<string> input{"..9748...",
			     "7........",
			     ".2.1.9...",
			     "..7...24.",
			     ".64.1.59.",
			     ".98...3..",
			     "...8.3.2.",
			     "........6",
			     "...2759.."};
	vector<vector<char>>board;
	for (const auto &s : input) {
		vector<char> vc;
		for (const char c : s)
			vc.push_back(c);
		board.push_back(vc);
	}
	Solution s;
	s.solveSudoku(board);
	for (const auto &row : board) {
		for (const char c : row)
			cout << c << " ";
		cout << endl;
	}

        return 0;
}
