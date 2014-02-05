/*
http://oj.leetcode.com/problems/pascals-triangle/
Sun Jan 12 00:19:28 EST 2014


Pascal's Triangle

Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
public:
	vector<vector<int> > generate(int numRows) {
		vector<vector<int> > result;
		for (size_t n = 1; n <= numRows; ++n) {
			result.push_back(vector<int>(n, 1));
			if (n > 2) {
				vector<int> &u = result[result.size()-2];
				vector<int> &v = result.back();
				for (size_t i = 1; i <= v.size()-2; ++i)
					v[i] = u[i-1] + u[i];
			}
		}
		return result;
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
	vector<vector<int> > v = s.generate(n);
	for (size_t i = 0; i < v.size(); ++i) {
		copy(v[i].begin(), v[i].end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	return 0;
}

