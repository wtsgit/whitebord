/*
http://oj.leetcode.com/problems/word-break/
Fri Jan  3 21:53:21 EST 2014


Word Break

Given a string s and a dictionary of words dict, determine if s can
be segmented into a space-separated sequence of one or more dictionary
words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

typedef ptrdiff_t ssize_t;

/*
	(0, 0) (0, 1) (0, 2) (0, 3)

	       (1, 1) (1, 2) (1, 3)

		      (2, 2) (2, 3)

			     (3, 3)
*/

class MySolution {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		size_t n = s.size();
		typedef bool *boolptr;
		boolptr *breakable = new boolptr[n];
		for (size_t i = 0; i < n; ++i)
			breakable[i] = new bool[n];
		for (size_t l = 1; l <= n; ++l) {
			for (size_t i = 0; i < n-l+1; ++i) {
				size_t j = i+l-1;
				breakable[i][j] = (dict.find(s.substr(i, l)) != dict.end());
				if (!breakable[i][j]) {
					for (size_t k = i; k < j; ++k) {
						if (breakable[i][k] && breakable[k+1][j]) {
							breakable[i][j] = true;
							break;
						}
					}
				}
			}
		}
		bool res = breakable[0][n-1];
		for (size_t i = 0; i < n; ++i)
			delete [] breakable[i];
		delete [] breakable;
		return res;
	}
};


/*
A simpler solution from leetcode discussion.

Check "MySolution". Notice we dont really need every breakable(i, j)
where 0 =< i <= j < n. We only care about breakable(i, n-1).

Assume the string of size n is breakable as
	[0, x1) [x1, x2) ... [x_k-1, n)
For every break point x_i, breakable[x_i] == true.

If the string n is also breakable as
	[0, y1) [y1, y2) ... [y_l-1, n)
The for every break point y_i, breakable[y_i] == true.

Note abjacent break points does not necessarily form word boundary.
E.g. [x_i, x_i+1)[y_j, y_j+1) where [x_i+1, y_j) is not necessarily
a word or breakable.

For each method to break the word, we could have a boolean vector
to indicate the break points.  The boolean vector in the code can
be viewed as formed by "ORing" all boolean vectors.

The code does not check every possible word-break. Shared break points
will only be set to true once.

*/
class Solution1 {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		size_t n = s.size();
		vector<bool> breakable(n+1, false);
		breakable[n] = true;
		for (ssize_t i = n-1; i >= 0; --i) {
			for (ssize_t j = i; j <= n-1; ++j) {
				if (dict.find(s.substr(i, j-i+1)) != dict.end() && breakable[j+1]) {
					breakable[i] = true;
					break;
				}
			}
		}
		return breakable[0];
	}
};


/*
Further optimization since we can construct a jump table to avoid
unnecessary linear search of the boolean array.
*/
class Solution {
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		size_t n = s.size();
		vector<ssize_t> breakable(n+1, -1);
		int jump = n;
		for (ssize_t i = n-1; i >= 0; --i) {
			for (ssize_t j = jump; j != -1; j = breakable[j]) {
				if (dict.find(s.substr(i, j-i)) != dict.end()) {
					breakable[i] = jump;
					jump = i;
					break;
				}
			}
		}

		return (breakable[0] != -1);
	}
};


int main()
{
	Solution s;
	unordered_set<string> dict;

	dict.insert("leet");
	dict.insert("code");
	if (s.wordBreak("leetcode", dict))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	dict.clear();
	dict.insert("cat");
	dict.insert("cats");
	dict.insert("and");
	dict.insert("sand");
	dict.insert("dog");
	if (s.wordBreak("catsanddog", dict))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	dict.clear();
	dict.insert("car");
	dict.insert("ca");
	dict.insert("rs");
	if (s.wordBreak("cars", dict))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	dict.clear();
	dict.insert("aaaa");
	dict.insert("aaa");
	if (s.wordBreak("aaaaaaa", dict))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	return 0;
}
