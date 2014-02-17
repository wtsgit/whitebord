/*
http://oj.leetcode.com/problems/3sum/
Sun Feb 16 20:46:33 EST 2014


3Sum

Given an array S of n integers, are there elements a, b, c in S
such that a + b + c = 0? Find all unique triplets in the array which
gives the sum of zero.

Note:

    Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
    The solution set must not contain duplicate triplets.

    For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)
*/

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<vector<int> > threeSum(vector<int> &num) {
		vector<vector<int>> rv;
		if (num.size() < 3)
			return rv;
		unordered_map<int, size_t> mp;
		for (auto val : num)
			++mp[val];
		num.clear();
		for (auto &kv : mp)
			num.push_back(kv.first);
		sort(num.begin(), num.end());
		for (size_t i = 0; i < num.size(); ++i) {
			auto it_i = mp.find(num[i]);
			--it_i->second;
			for (size_t j = i; j < num.size(); ++j) {
				auto it_j = mp.find(num[j]);
				if (it_j->second == 0)
					continue;
				--it_j->second;
				int expected = -(num[i]+num[j]);
				if (expected >= num[j]) {
					auto it_expected = mp.find(expected);
					if (it_expected != mp.end() && it_expected->second > 0) {
						rv.push_back({num[i], num[j], expected});
					}
				}
				++it_j->second;
			}
			++it_i->second;
		}
		return rv;
	}
};

int main() {
	vector<int> S = {-1,0,1,2,-1,-4};
	Solution s;
	auto rv = s.threeSum(S);
	for (auto &v : rv) {
		for (auto x : v)
			cout << x << " ";
		cout << endl;
	}
	return 0;
}
