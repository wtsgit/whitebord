/*
http://oj.leetcode.com/problems/permutations/
Sun Feb  9 21:09:27 EST 2014


Permutations

Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
*/

#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<vector<int> > permute(vector<int> &num) {
		vector<vector<int>> rv;
		stack<pair<size_t, size_t>> st;
		if (num.size() == 0)
			return rv;
		st.push({0, 0});
		while (!st.empty()) {
			auto &start = st.top().first;
			auto &next = st.top().second;
			if (!(start < num.size())) {
				rv.push_back(num);
				st.pop();
				continue;
			}
			if (!(next < num.size())) {
				swap(num[start], num[next-1]);
				st.pop();
				continue;
			}
			if (start < next) {
				swap(num[start], num[next-1]);
				swap(num[start], num[next]);
			}
			++next;
			st.push({start+1, start+1});
		}
		return rv;
	}
};

int main() {
	vector<int> v{1, 2, 3, 4};
	Solution s;
	auto rv = s.permute(v);
	for (auto v : rv) {
		for (auto i : v)
			cout << i << " ";
		cout << endl;
	}
	return 0;
}
