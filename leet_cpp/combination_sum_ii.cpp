/*
http://oj.leetcode.com/problems/combination-sum/
Tue Feb 11 22:27:02 EST 2014


Combination Sum II

Given a collection of candidate numbers (C) and a target number
(T), find all unique combinations in C where the candidate numbers
sums to T.

Each number in C may only be used once in the combination.

Note:

    All numbers (including target) will be positive integers.

    Elements in a combination (a1, a2, … , ak) must be in non-descending
    order. (ie, a1 ≤ a2 ≤ … ≤ ak).

    The solution set must not contain duplicate combinations.

For example, given candidate set 10,1,2,7,6,1,5 and target 8,

A solution set is:

[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6] 
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
		auto it = be;
		while (it != en) {
			if (*it > target)
				break;
			auto ub = it;
			while (ub != en && *ub == *it)
				++ub;
			int n = ub - it;
			for (int i = 1; i <= n && *it*i <= target; ++i) {
				vector<int> np(partial);
				np.resize(np.size()+i, *it);
				helper(vv, np, ub, en, target-*it*i);
			}
			it = ub;
		}
	}
public:
	vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
		vector<vector<int>> vv;
		std::sort(candidates.begin(), candidates.end());
		helper(vv, vector<int>(), candidates.begin(), candidates.end(), target);
		return vv;
	}
};

int main() {
	{
		Solution s;
		vector<int> vi{2,3,6,7};
		auto vv = s.combinationSum2(vi,7);
		for (auto v : vv) {
			for (auto x : v)
				cout << x << " ";
			cout << endl;
		}
	}
	{
		Solution s;
		vector<int> vi{1,2,2,5,5,10};
		auto vv = s.combinationSum2(vi,20);
		for (auto v : vv) {
			for (auto x : v)
				cout << x << " ";
			cout << endl;
		}
	}
	{
		Solution s;
		vector<int> vi{10,1,2,7,6,1,5};
		auto vv = s.combinationSum2(vi,8);
		for (auto v : vv) {
			for (auto x : v)
				cout << x << " ";
			cout << endl;
		}
	}
	return 0;
}
