/*
http://oj.leetcode.com/problems/word-search/
Fri Jan 31 00:49:33 EST 2014


Word Search

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent
cell, where "adjacent" cells are those horizontally or vertically
neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]

word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/

#include <vector>
#include <string>
#include <unordered_set>
#include <stack>
#include <iostream>

using namespace std;

struct Loc { // Location in matrix
	size_t i, j;
};

// From boost
template<class T>
inline void hash_combine(std::size_t &seed, T const &v) {
	std::hash<T> hfn;
	seed ^= hfn(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

struct LocHash {
	std::size_t operator() (const Loc &loc) const {
		std::size_t seed = 0;
		hash_combine(seed, loc.i);
		hash_combine(seed, loc.j);
		return seed;
	}
};

struct LocEqual {
	bool operator()(const Loc &loc1, const Loc &loc2) const  {
		return loc1.i == loc2.i && loc1.j == loc2.j;
	}
};

struct Match {
	Loc loc;
	size_t k;
	int ne;
};

class Solution {
public:
	int getNe(const vector<vector<char>> &board, Loc &loc, int ne) {
		int next_ne = -1;
		switch (ne) {
		case 0:
			next_ne = 1;
			if (loc.i > 0) {
				loc.i -= 1;
				break;
			}
		case 1:
			next_ne = 2;
			if (loc.i < board.size()-1) {
				loc.i += 1;
				break;
			}
		case 2:
			next_ne = 3;
			if (loc.j > 0) {
				loc.j -= 1;
				break;
			}
		case 3:
			next_ne = 4;
			if (loc.j < board[loc.i].size()-1) {
				loc.j += 1;
				break;
			}
		default:
			next_ne = -1;
		}
		return next_ne;
	}

	bool exist(vector<vector<char> > &board, string word) {
		if (word.size() == 0)
			return true;
		for (size_t i = 0; i < board.size(); ++i) {
			for (size_t j = 0; j < board[i].size(); ++j) {
				if (board[i][j] == word[0]) {
					unordered_set<Loc, LocHash, LocEqual> visited;
					stack<Match> match;
					match.push({{i, j}, 0, 0});
					visited.insert({i, j});
					while (!match.empty()) {
						size_t k = match.top().k;
						if (k == word.size()-1)
							return true;
						Loc &loc = match.top().loc;
						Loc ne_loc = loc;
						int ne = getNe(board, ne_loc, match.top().ne);
						if (ne < 0) {
							visited.erase({loc.i, loc.j});
							match.pop();
						}
						else {
							match.top().ne = ne;
							if (visited.find(ne_loc) == visited.end()
							    && board[ne_loc.i][ne_loc.j] == word[k+1]) {
								match.push({ne_loc, k+1, 0});
								visited.insert({ne_loc.i, ne_loc.j});
							}
						}
					}
				}
			}
		}
		return false;
	}
};

int main()
{
	vector<vector<char>> v = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
	Solution s;

	cout << "ABCCED" << " " << s.exist(v, "ABCCED") << endl;
	cout << "SEE" << " " << s.exist(v, "SEE") << endl;
	cout << "ABCB" << " " << s.exist(v, "ABCB") << endl;
	return 0;
}
