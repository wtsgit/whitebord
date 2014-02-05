/*
http://oj.leetcode.com/problems/generate-parentheses/
Tue Jan 28 00:10:56 EST 2014


Generate Parentheses

Given n pairs of parentheses, write a function to generate all
combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;


class Solution {
private:
	void gen(vector<string> &vs, vector<int> &right_p, size_t start, size_t k) {
		if (start == right_p.size()-1) {
			vs.emplace_back();
			string &s = vs.back();
			right_p[start] = k;
			s.reserve(2 * right_p.size());
			for (auto x : right_p) {
				s.push_back('(');
				s.resize(s.size()+x, ')');
			}
			return;
		}
		for (size_t j = 0; j <= start+1+k-right_p.size(); ++j) {
			right_p[start] = j;
			gen(vs, right_p, start+1, k-j);
		}
	}
public:
	vector<string> generateParenthesis(int n) {
		vector<int> right_p(n);
		vector<string> vs;
		gen(vs, right_p, 0, n);
		return vs;
	}
};

int main(int argc, char **argv) {
	if (argc < 2)
		return 1;
	istringstream iss(argv[1]);
	int n;
	iss >> n;
	Solution s;
	vector<string> vs = s.generateParenthesis(n);
	copy (vs.begin(), vs.end(), ostream_iterator<string>(cout, "\n"));

	return 0;
}
