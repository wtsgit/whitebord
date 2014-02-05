/*
http://oj.leetcode.com/problems/subsets/
Wed Jan 22 12:08:34 EST 2014


Subsets

Given a set of distinct integers, S, return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If S = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<vector<int> > subsets(vector<int> &S) {
		std::sort(S.begin(), S.end());
		size_t n = (size_t)1 << S.size();
		vector<vector<int> > result(n);
		for (size_t i = 0; i < S.size(); ++i) {
			n = (size_t)1 << i;
			for (size_t j = 0; j < n; ++j) {
				result[n+j] = result[j];
				result[n+j].push_back(S[i]);
			}
		}
		return result;
	}
};

int main() {
	vector<int> S{1};
	Solution s;
	auto result = s.subsets(S);
	for (auto x : result) {
		for (auto y : x)
			cout << y << " ";
		cout << endl;
	}
	return 0;
}

