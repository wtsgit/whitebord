/*
http://oj.leetcode.com/problems/permutations/
Sun Feb  9 22:13:15 EST 2014


Permutations II

Given a collection of numbers that might contain duplicates, return
all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].
*/

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
private:
	void helper(vector<vector<int>> &rv, vector<int> &num, size_t start) {
		if (start == num.size()) {
			rv.push_back(num);
		}
		unordered_set<int> se;
		for (size_t i = start; i < num.size(); ++i) {
			if (se.find(num[i]) == se.end()) {
				se.insert(num[i]);
				swap(num[start], num[i]);
				helper(rv, num, start+1);
				swap(num[start], num[i]);
			}
		}
	}
public:
	vector<vector<int> > permuteUnique(vector<int> &num) {
		vector<vector<int>> rv;
		if (num.size() == 0)
			return rv;
		sort(num.begin(), num.end());
		helper(rv, num, 0);
		return rv;
	}
};

int main() {
	vector<int> v{0,0,0,1,9};
	Solution s;
	auto rv = s.permuteUnique(v);
	for (auto v : rv) {
		for (auto i : v)
			cout << i << " ";
		cout << endl;
	}
	return 0;
}
