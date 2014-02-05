/*
http://oj.leetcode.com/problems/surrounded-regions/
Mon Jan  6 23:27:15 EST 2014


Surrounded Regions

Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef ptrdiff_t ssize_t;

class Solution {
public:
	void solve(vector<vector<char> > &board) {
		const ssize_t h = board.size();
		if (h == 0)
			return;
		const ssize_t w = board[0].size();
		if (w == 0)
			return;

		stack<pair<ssize_t, ssize_t> > s;
		for (ssize_t i = 0; i < w; ++i)
			if (board[0][i] == 'O')
				s.push(make_pair(0, i));

		for (ssize_t i = 0; i < w; ++i)
			if (board[h-1][i] == 'O')
				s.push(make_pair(h-1, i));

		for (ssize_t i = 0; i < h; ++i)
			if (board[i][0] == 'O')
				s.push(make_pair(i, 0));

		for (ssize_t i = 0; i < h; ++i)
			if (board[i][w-1] == 'O')
				s.push(make_pair(i, w-1));

		while (!s.empty()) {
			ssize_t i = s.top().first;
			ssize_t j = s.top().second;
			s.pop();
			board[i][j] = 'E';
			if (i-1 >= 0 && board[i-1][j] == 'O')
				s.push(make_pair(i-1, j));
			if (i+1 <= h-1 && board[i+1][j] == 'O')
				s.push(make_pair(i+1, j));
			if (j-1 >= 0 && board[i][j-1] == 'O')
				s.push(make_pair(i, j-1));
			if (j+1 <= w-1 && board[i][j+1] == 'O')
				s.push(make_pair(i, j+1));
		}

		//capture and unmark
		for (ssize_t i = 0; i < h; ++i) {
			for (ssize_t j = 0; j < w; ++j) {
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				if (board[i][j] == 'E')
					board[i][j] = 'O';
			}
		}
	}
};

int main()
{
	vector<vector<char> > board(4);
	board[0].push_back('X');
	board[0].push_back('X');
	board[0].push_back('X');
	board[0].push_back('X');

	board[1].push_back('X');
	board[1].push_back('O');
	board[1].push_back('O');
	board[1].push_back('X');

	board[2].push_back('X');
	board[2].push_back('X');
	board[2].push_back('O');
	board[2].push_back('X');

	board[3].push_back('X');
	board[3].push_back('O');
	board[3].push_back('X');
	board[3].push_back('X');

	Solution s;
	s.solve(board);

	for (ssize_t i = 0; i < board.size(); ++i) {
		for (ssize_t j = 0; j < board[i].size(); ++j) {
			cout << board[i][j];
		}
		cout << endl;
	}

	return 0;
}

