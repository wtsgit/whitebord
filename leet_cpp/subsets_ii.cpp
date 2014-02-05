/*
http://oj.leetcode.com/problems/subsets-ii/
Wed Jan 22 14:54:15 EST 2014


Subsets II

Given a collection of integers that might contain duplicates, S,
return all possible subsets.

Note:

    Elements in a subset must be in non-descending order.
    The solution set must not contain duplicate subsets.

For example,
If S = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
	vector<vector<int> > subsets(vector<int> &S) {
		unordered_map<int, size_t> mp;
		for (auto x : S)
			++mp[x];
		vector<int> uS;
		for (auto kv : mp)
			uS.push_back(kv.first);
		std::sort(uS.begin(), uS.end());
		size_t n = 1;
		for (auto x : uS)
			n *= (mp[x]+1);
		vector<vector<int> > result(n);
		n = 1;
		for (auto x : uS) {
			size_t c = mp[x];
			for (size_t i = 1; i <= c; ++i) {
				size_t start = n*i;
				for (size_t j = 0; j < n; ++j) {
					result[j+start] = result[j];
					for (size_t k = 0; k < i; ++k) {
						result[j+start].push_back(x);
					}
				}
			}
			n *= c+1;
		}
		return result;
	}
};

int main() {
	vector<int> S{1, 2, 2};
	Solution s;
	auto result = s.subsets(S);
	for (auto x : result) {
		for (auto y : x)
			cout << y << " ";
		cout << endl;
	}
	return 0;
}
