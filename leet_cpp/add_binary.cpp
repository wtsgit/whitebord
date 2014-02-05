/*
http://oj.leetcode.com/problems/add-binary/
Mon Feb  3 17:36:42 EST 2014


Add Binary

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
	string addBinary(string a, string b) {
		std::reverse(a.begin(), a.end());
		std::reverse(b.begin(), b.end());
		string::const_iterator ita = a.begin();
		string::const_iterator itb = b.begin();
		string c;
		int carry = 0;
		while (ita != a.end() || itb != b.end()) {
			int i = 0;
			if (ita != a.end()) {
				i = *ita - '0';
				++ita;
			}
			int j = 0;
			if (itb != b.end()) {
				j = *itb - '0';
				++itb;
			}
			int k = i+j+carry;
			carry = k/2;
			k %= 2;
			if (k) c.push_back('1'); else c.push_back('0');
		}
		if (carry)
			c.push_back('1');
		std::reverse(c.begin(), c.end());
		return c;
	}
};

int main()
{
        return 0;
}
