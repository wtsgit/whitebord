/*
http://oj.leetcode.com/problems/roman-to-integer/
Sat Feb 15 19:47:25 EST 2014


Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
	int romanToInt(string s) {
		struct Conv {
			int divisor;
			char high, mid, low;
		};
		vector<Conv> conv{ {1000, '$', '$', 'M'},
				   {100,  'M', 'D', 'C'},
				   {10,   'C', 'L', 'X'},
				   {1,    'X', 'V', 'I'} };
		int roman = 0;
		size_t i = 0;
		for (const auto &cv : conv) {
			if (i < s.size() && s[i] == cv.mid) {
				roman += 5 * cv.divisor;
				++i;
				size_t n_low = 0;
				while (i < s.size() && s[i] == cv.low) {
					++n_low;
					++i;
				}
				if (n_low > 3)
					return 0;
				roman += n_low * cv.divisor;
			}
			else if (i < s.size() && s[i] == cv.low) {
				size_t n_low = 0;
				while (i < s.size() && s[i] == cv.low) {
					++n_low;
					++i;
				}
				if (n_low > 3)
					return 0;
				if (i < s.size() && s[i] == cv.mid) {
					roman += 5 * cv.divisor;
					roman -= n_low * cv.divisor;
					++i;
				}
				else if (i < s.size() && s[i] == cv.high) {
					roman += 10 * cv.divisor;
					roman -= n_low * cv.divisor;
					++i;
				}
				else {
					roman += n_low * cv.divisor;
				}
			}
		}
		if (i < s.size())
			return 0;
		return roman;
	}
};

int main() {
	Solution s;
	cout << s.romanToInt("MCMLIV") << endl;
	cout << s.romanToInt("MCMXC") << endl;
	cout << s.romanToInt("MMXIV") << endl;
	return 0;
}
