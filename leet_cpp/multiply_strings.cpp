/*
http://oj.leetcode.com/problems/multiply-strings/
Tue Feb 11 17:24:37 EST 2014


Multiply Strings

Given two numbers represented as strings, return multiplication of
the numbers as a string.

Note: The numbers can be arbitrarily large and are non-negative.
*/
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
private:
	string addHelper(string num1, string num2) {
		string r;
		size_t n = min(num1.size(), num2.size());
		int carry = 0;
		int sum = 0;
		size_t i = 0;
		for (i = 0; i < n; ++i) {
			sum = num1[i]-'0' + num2[i]-'0' + carry;
			carry = sum / 10;
			sum = sum % 10;
			r.push_back('0'+sum);
		}
		while (i < num1.size()) {
			sum = num1[i]-'0' + carry;
			carry = sum / 10;
			sum = sum % 10;
			r.push_back('0'+sum);
			++i;
		}
		while (i < num2.size()) {
			sum = num2[i]-'0' + carry;
			carry = sum / 10;
			sum = sum % 10;
			r.push_back('0'+sum);
			++i;
		}
		if (carry) {
			r.push_back('1');
		}
		return r;
	}

public:
	string multiply(string num1, string num2) {
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		string prod;
		for (size_t i = 0; i < num1.size(); ++i) {
			string partial_prod(i, '0');
			int carry = 0;
			for (size_t j = 0; j < num2.size(); ++j) {
				int prod = (num1[i]-'0') * (num2[j]-'0') + carry;
				carry = prod / 10;
				prod = prod % 10;
				partial_prod.push_back('0'+prod);
			}
			if (carry)
				partial_prod.push_back('0'+carry);
			prod = addHelper(prod, partial_prod);
		}
		while (prod.size() > 1) {
			auto it = prod.end();
			--it;
			if (*it == '0')
				prod.erase(it);
			else
				break;
		}
		reverse(prod.begin(), prod.end());
		return prod;
	}
};

int main(int argc, char **argv) {
	if (argc < 3)
		return 1;
	Solution s;
	cout << s.multiply(argv[1], argv[2]) << endl;
	return 0;
}
