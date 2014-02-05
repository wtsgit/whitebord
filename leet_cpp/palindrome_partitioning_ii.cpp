/*
http://oj.leetcode.com/problems/palindrome-partitioning-ii/
Mon Jan  6 22:06:40 EST 2014


Palindrome Partitioning II

Given a string s, partition s such that every substring of the
partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be
produced using 1 cut.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

typedef ptrdiff_t ssize_t;

class Solution {
public:
	bool debug_on;
	Solution() : debug_on(false) {}

	void palindrome_prefix(vector<vector<size_t> > &P, const string &s) {
		const size_t n = s.size();
		P.clear();
		P.resize(n);
		for (size_t i = 0; i < 2*n-1; ++i) {
			ssize_t j =  i/2;
			ssize_t k = j;
			if (i & 1) ++k;
			ssize_t l = (i&1) ? 2 : 1;
			ssize_t t = 0;
			while (j-t >= 0 && k+t <= n-1 && s[j-t] == s[k+t]) {
				assert(j-t < P.size());
				P[j-t].push_back(l);
				l += 2;
				t += 1;
			}
		}
	}

	struct Cut { size_t n; size_t next; };
	int minCut(string s) {
		if (s.empty())
			return 0;
		const size_t n = s.size();
		vector<vector<size_t> > prefix;
		palindrome_prefix(prefix, s);
		vector<Cut> cut(s.size()+1);
		if (debug_on) cout << endl;
		for (ssize_t i = n-1; i >= 0; --i) {
			size_t min_cut = 1+cut[i+prefix[i][0]].n;
			size_t next = i+prefix[i][0];
			for (size_t j = 1; j < prefix[i].size(); ++j) {
				if (1+cut[i+prefix[i][j]].n < min_cut) {
					min_cut = 1+cut[i+prefix[i][j]].n;
					next = i+prefix[i][j];
				}
			}
			cut[i].n = min_cut;
			cut[i].next = next;
			if (debug_on) cout << "cut[" << i << "]" << cut[i].n << ", " << cut[i].next << endl;
		}

		if (debug_on) {
			for (size_t i = 0; i < s.size(); i = cut[i].next) {
				cout << s.substr(i, cut[i].next-i) << " ";
			}
			cout << endl;
		}

		return cut[0].n-1;
	}
};


int main(int argc, char **argv)
{
	if (argc <= 1) {
		return 0;
	}

	Solution s;

	vector<vector<size_t> > Prefix;
	s.palindrome_prefix(Prefix, argv[1]);
	cout << endl;
	for (size_t i = 0; i < Prefix.size(); ++i) {
		cout << argv[1][i] << ": ";
		for (size_t j = 0; j < Prefix[i].size(); ++j) {
			cout << Prefix[i][j] << " ";
		}
		cout << endl;
	}

	s.debug_on = true;
	cout << "min cut: " << s.minCut(argv[1]) << endl;

	return 0;
}
