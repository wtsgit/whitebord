/*
http://oj.leetcode.com/problems/3sum-closest/
Sun Feb 16 22:10:34 EST 2014


3Sum Closest

Given an array S of n integers, find three integers in S such that
the sum is closest to a given number, target. Return the sum of the
three integers. You may assume that each input would have exactly
one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
	int threeSumClosest(vector<int> &num, int target) {
		sort(num.begin(), num.end());
		int diff = INT_MAX;
		int sum = 0;
		for (auto ita = num.begin(); ita != num.end(); ++ita) {
			for (auto itb = ita+1; itb != num.end(); ++itb) {
				int c = target - *ita - *itb;
				auto itc = lower_bound(itb+1, num.end(), c);
				if (itc != num.end()) {
					int new_sum = *ita + *itb + *itc;
					if (abs(target - new_sum) < diff) {
						diff = abs(target - new_sum);
						sum = new_sum;
					}
				}
				if (itc != itb+1) {
					int new_sum = *ita + *itb + *(itc-1);
					if (abs(target - new_sum) < diff) {
						diff = abs(target - new_sum);
						sum = new_sum;
					}
				}
			}
		}
		return sum;
	}
};

int main() {
	Solution s;
	vector<int> S{-1,2,1,-4};
	cout << s.threeSumClosest(S, 1) << endl;
	return 0;
}
