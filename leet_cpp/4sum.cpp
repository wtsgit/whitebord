/*
http://oj.leetcode.com/problems/4sum/
Mon Feb 17 15:08:06 EST 2014


4Sum

Given an array S of n integers, are there elements a, b, c, and d
in S such that a + b + c + d = target? Find all unique quadruplets
in the array which gives the sum of target.

Note:

    Elements in a quadruplet (a,b,c,d) must be in non-descending
    order. (ie, a ≤ b ≤ c ≤ d)

    The solution set must not contain duplicate quadruplets.

    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<vector<int> > fourSum(vector<int> &num, int target) {
		vector<vector<int>> vvi;

		sort(num.begin(), num.end());
		struct Sum {
			int sum;
			size_t i, j;
		};
		vector<Sum> sums;
		for (size_t i = 0; i < num.size(); ++i) {
			for (size_t j = i+1; j < num.size(); ++j) {
				sums.push_back({num[i]+num[j], i, j});
			}
		}
		stable_sort(sums.begin(), sums.end(), [](const Sum &a, const Sum &b){ return a.sum < b.sum; });
		for (size_t i = 0; i < num.size(); ++i) {
			if (i > 0 && num[i] == num[i-1])
				continue;
			for (size_t j = i+1; j < num.size(); ++j) {
				if (j > i+1 && num[j] == num[j-1])
					continue;
				Sum expected{target-num[i]-num[j], j, 0};
				auto lb = lower_bound(sums.begin(), sums.end(),
							expected,
							[](const Sum &a, const Sum &b){ return a.sum < b.sum; });
				auto ub = upper_bound(lb, sums.end(),
							expected,
							[](const Sum &a, const Sum &b){ return a.sum < b.sum; });
				auto start = upper_bound(lb, ub, expected,
							[](const Sum &a, const Sum &b){ return a.i < b.i; });
				for (auto it = start; it != ub; ++it) {
					if (it != start && num[it->i] == num[(it-1)->i])
						continue;
					vvi.push_back({num[i], num[j], num[it->i], num[it->j]});
				}
			}
		}

		return vvi;
	}
};

int main() {
	//vector<int> S{1,0,-1,0,-2,2};
	vector<int> S{-3,-2,-1,0,0,1,2,3};
	Solution s;
	auto vvi = s.fourSum(S, 0);
	for (auto &vi : vvi) {
		for (auto i : vi) {
			cout << i << " ";
		}
		cout << endl;
	}
	return 0;
}
