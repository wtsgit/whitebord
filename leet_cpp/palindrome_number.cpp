/*
http://oj.leetcode.com/problems/palindrome-number/
Fri Jan 24 21:48:56 EST 2014


Palindrome Number

Determine whether an integer is a palindrome. Do this without extra space.

Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the
restriction of using extra space.

You could also try reversing an integer. However, if you have solved
the problem "Reverse Integer", you know that the reversed integer
might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/
#include <iostream>
#include <cstdlib>
using namespace std;

class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0)
			return false;
		int n = 0;
		int d = 1;
		while (x/d >= 10 || x/d <= -10) {
			d *= 10;
			++n;
		}
		if (n == 0)
			return true;
		for (int i = 0; i < (n+1)/2; ++i) {
			int h = x/d;
			int l = x % 10;
			if (h != l)
				return false;
			x %= d;
			x /= 10;
			d /= 100;
		}
		return true;
	}
};

int main(int argc, char **argv) {
	if (argc < 2)
		return 1;
	Solution s;
	cout << s.isPalindrome(atoi(argv[1])) << endl;
	return 0;
}
