/*
http://oj.leetcode.com/problems/count-and-say/
Tue Feb 11 22:48:23 EST 2014


Count and Say

The count-and-say sequence is the sequence of integers beginning
as follows:

1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	string countAndSay(int n) {
		string s;
		if (n <= 0)
			return s;
		s = "1";
		if (n == 1)
			return s;
		while (--n > 0) {
			string ns;
			auto it = s.cbegin();
			while (it != s.cend()) {
				auto ub = it;
				while (ub != s.cend() && *ub == *it)
					++ub;
				ns += to_string(ub-it);
				ns += *it;
				it = ub;
			}
			s = ns;
		}
		return s;
	}
};

int main() {
	Solution s;
	cout << s.countAndSay(4) << endl;
	return 0;
}
