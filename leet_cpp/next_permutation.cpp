/*
http://oj.leetcode.com/problems/next-permutation/
Thu Feb 13 16:20:28 EST 2014


Next Permutation

Implement next permutation, which rearranges numbers into the
lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the
lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its
corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	void nextPermutation(vector<int> &num) {
		if (num.size() <= 1)
			return;
		auto it = num.end();
		do {
			--it;
			if ((it+1) != num.end() && *it < *(it+1)) {
				reverse(it+1, num.end());
				auto ub = upper_bound(it+1, num.end(), *it);
				swap(*it, *ub);
				return;
			}
		} while (it != num.begin());
		reverse(num.begin(), num.end());
	}
};

int main() {
	{
		vector<int> v{1, 2, 3};
		Solution s;
		s.nextPermutation(v);
		for (auto x : v)
			cout << x << " ";
		cout << endl;
	}
	{
		vector<int> v{3, 2, 1};
		Solution s;
		s.nextPermutation(v);
		for (auto x : v)
			cout << x << " ";
		cout << endl;
	}
	{
		vector<int> v{1, 1, 5};
		Solution s;
		s.nextPermutation(v);
		for (auto x : v)
			cout << x << " ";
		cout << endl;
	}
	return 0;
}
