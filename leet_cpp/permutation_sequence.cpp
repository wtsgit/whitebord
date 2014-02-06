/*
http://oj.leetcode.com/problems/permutation-sequence/
Thu Feb  6 15:35:47 EST 2014


Permutation Sequence

The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

    "123"
    "132"
    "213"
    "231"
    "312"
    "321"

Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>

using namespace std;

class Solution {
public:
	string getPermutation(int n, int k) {
		string s;
		if (n < 1 || n > 9)
			return s;
		vector<int> fact(n+1, 1);
		for (int i = 1; i <= n; ++i) {
			fact[i] = i * fact[i-1];
		}
		if (k <= 0 || k > fact[n])
			return s;
		--k;
		vector<bool> used(10, false);
		for (int i = n-1; i >= 0; --i) {
			int x = k/fact[i]+1;
			int t = 0;
			int j = 0;
			for (j = 1; j < (int)used.size(); ++j) {
				if (used[j] == false)
					++t;
				if (t == x)
					break;
			}
			assert(j < (int)used.size());
			used[j] = true;
			s.push_back((char)('0' + j));
			k %= fact[i];
		}
		return s;
	}
};

int main(int argc, char **argv)
{
	if (argc < 3)
		return 1;
	Solution s;
	cout << s.getPermutation(atoi(argv[1]), atoi(argv[2])) << endl;
        return 0;
}
