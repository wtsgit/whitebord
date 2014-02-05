/*
http://oj.leetcode.com/problems/pascals-triangle-ii/
Sun Jan 12 00:01:35 EST 2014


Pascal's Triangle II

Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> v;
		for (size_t n = 0; n <= rowIndex; ++n) {
			v.push_back(1);
			if (v.size() > 2) {
				for (size_t i = v.size()-2; i >= 1; --i)
					v[i] += v[i-1];
			}
		}
		return v;
	}
};

int main(int argc, char **argv)
{
	if (argc <= 1) {
		return 0 ;
	}
	stringstream ss(argv[1]);
	int n;
	ss >> n;
	Solution s;
	vector<int> v = s.getRow(n);
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}

