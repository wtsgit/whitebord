/*
http://oj.leetcode.com/problems/combination-sum/
Tue Feb 11 20:41:34 EST 2014


Combination Sum

Given a set of candidate numbers (C) and a target number (T), find
all unique combinations in C where the candidate numbers sums to
T.

The same repeated number may be chosen from C unlimited number of times.

Note:

    All numbers (including target) will be positive integers.

    Elements in a combination (a1, a2, … , ak) must be in non-descending
    order. (ie, a1 ≤ a2 ≤ … ≤ ak).

    The solution set must not contain duplicate combinations.

For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
	void helper(vector<vector<int>> &vv,
			const vector<int> &partial,
			const vector<int>::const_iterator be,
			const vector<int>::const_iterator en,
			const int target) {

		if (target == 0) {
			vv.push_back(partial);
			return;
		}
		for (auto it = be; it != en; ++it) {
			if (*it > target)
				break;
			int i = 1;
			while (*it*i <= target) {
				vector<int> np(partial);
				np.resize(np.size()+i, *it);
				helper(vv, np, it+1, en, target-*it*i);
				++i;
			}
		}
	}
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int>> vv;
		std::sort(candidates.begin(), candidates.end());
		auto uniq_end = std::unique(candidates.begin(), candidates.end());
		helper(vv, vector<int>(), candidates.begin(), uniq_end, target);
		return vv;
	}
};

int main() {
	{
		Solution s;
		vector<int> vi{2,3,6,7};
		auto vv = s.combinationSum(vi,7);
		for (auto v : vv) {
			for (auto x : v)
				cout << x << " ";
			cout << endl;
		}
	}
	{
		Solution s;
		vector<int> vi{1,2,5,10};
		auto vv = s.combinationSum(vi,20);
		for (auto v : vv) {
			for (auto x : v)
				cout << x << " ";
			cout << endl;
		}
	}
	return 0;
}
