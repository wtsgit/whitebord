/*
http://oj.leetcode.com/problems/palindrome-partitioning/
Mon Jan  6 15:15:13 EST 2014


Palindrome Partitioning

Given a string s, partition s such that every substring of the
partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return
  [
    ["aa","b"],
    ["a","a","b"]
  ]
*/
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

typedef ptrdiff_t ssize_t;

class Solution {
public:
	void palindrome(vector<size_t> &P, const string &s) {
		const size_t n = s.size();
		P.clear();
		P.resize(2*n-1);
		for (size_t i = 0; i < P.size(); ++i) {
			ssize_t j =  i/2;
			ssize_t k = j;
			if (i & 1) ++k;
			ssize_t l = ((~i) & 1);
			ssize_t t = l;
			while (j-t >= 0 && k+t <= n-1 && s[j-t] == s[k+t]) {
				l += 2;
				t += 1;
			}
			P[i] = l;
		}
	}

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

	void substring_partition(vector<vector<string> > &collection,
			const vector<string> &prefix,
			const size_t start,
			const string &s,
			const vector<vector<size_t> > &P) {

		const size_t n = s.size();
		for (size_t i = 0; i < P[start].size(); ++i) {
			vector<string> new_prefix(prefix);
			new_prefix.push_back(s.substr(start, P[start][i]));
			if (start + P[start][i] < n) {
				substring_partition(collection, new_prefix, start+P[start][i], s, P);
			}
			else {
				collection.push_back(new_prefix);
			}
		}
	}

	vector<vector<string> > partition(string s) {
		vector<vector<size_t> > P;
		palindrome_prefix(P, s);
		vector<vector<string> > result;
		substring_partition(result, vector<string>(), 0, s, P);
		return result;
	}

};


int main(int argc, char **argv)
{
	if (argc <= 1) {
		return 0;
	}

	Solution s;

	vector<size_t> P;
	s.palindrome(P, argv[1]);
	for (size_t i = 0; i < P.size(); ++i) {
		if ((i & 1) == 0)
			cout << argv[1][i/2] << " ";
		else
			cout << "  ";
		cout << P[i] << endl;
	}

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

	vector<vector<string> > part = s.partition(argv[1]);

	for (size_t i = 0; i < part.size(); ++i) {
		for (size_t j = 0; j < part[i].size(); ++j) {
			cout << part[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
