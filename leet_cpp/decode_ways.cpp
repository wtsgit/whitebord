/*
http://oj.leetcode.com/problems/decode-ways/
Wed Jan 22 16:37:45 EST 2014


Decode Ways

A message containing letters from A-Z is being encoded to numbers
using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given an encoded message containing digits, determine the total
number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	int numDecodings(string s) {
		size_t n = 0;
		size_t n1 = 1;
		size_t n2 = 0;
		for (size_t i = s.size(); i > 0; --i) {
			n = 0;
			if (s[i-1] != '0')
				n = n1;
			if (i < s.size()) {
				if (s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6'))
					n += n2;
			}
			n2 = n1;
			n1 = n;
		}

		return n;
	}
};

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	Solution s;
	cout << s.numDecodings(argv[1]) << endl;
	return 0;
}
