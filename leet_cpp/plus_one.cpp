/*
http://oj.leetcode.com/problems/plus-one/
Mon Feb  3 15:51:17 EST 2014


Plus One

Given a number represented as an array of digits, plus one to the number.
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> plusOne(vector<int> &digits) {
		vector<int> r(digits);
		int carry = 1;
		for (vector<int>::reverse_iterator it = r.rbegin(); it != r.rend(); ++it) {
			*it += carry;
			carry = *it / 10;
			*it %= 10;
		}
		if (carry)
			r.insert(r.begin(), carry);
		return r;
	}
};

int main()
{
        return 0;
}
