/*
http://oj.leetcode.com/problems/combinations/
Fri Jan 31 01:48:09 EST 2014


Combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
	[2,4],
	[3,4],
	[2,3],
	[1,2],
	[1,3],
	[1,4],
]
*/

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Solution {
public:
	void combineSub(vector<vector<int>> &coll, vector<int> &v, int n, int k, int start) {
		if (k == 0) {
			coll.push_back(std::move(v));
			return;
		}
		for (int i = start; i <= n-k+1; ++i) {
			vector<int> nv(v);
			nv.push_back(i);
			combineSub(coll, nv, n, k-1, i+1);
		}
	}
	vector<vector<int> > combine(int n, int k) {
		vector<vector<int>> coll;
		vector<int> v;
		combineSub(coll, v, n, k, 1);
		return coll;
	}
};

int main(int argc, char **argv) {
	if (argc < 3)
		return 1;
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	Solution s;
	auto vvi = s.combine(n, k);
	for (auto &x : vvi) {
		for (auto &y : x)
			cout << y << " ";
		cout << endl;
	}
	return 0;
}
