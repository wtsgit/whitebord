/*
http://oj.leetcode.com/problems/integer-to-roman/
Sat Feb 15 19:16:24 EST 2014


Integer to Roman

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	string intToRoman(int num) {
		string roman;
		if (num > 3999 || num < 1) {
			return roman;
		}
		struct Conv {
			int divisor;
			char high, mid, low;
		};
		vector<Conv> conv{ {1000, '$', '$', 'M'},
				   {100,  'M', 'D', 'C'},
				   {10,   'C', 'L', 'X'},
				   {1,    'X', 'V', 'I'} };

		for (const auto &cv : conv) {
			int q = num / cv.divisor;
			num %= cv.divisor;
			switch (q) {
				case 1:
				case 2:
				case 3:
					roman.resize(roman.size()+q, cv.low);
					break;
				case 4:
					roman.push_back(cv.low);
					roman.push_back(cv.mid);
					break;
				case 5:
					roman.push_back(cv.mid);
					break;
				case 6:
				case 7:
				case 8:
					roman.push_back(cv.mid);
					roman.resize(roman.size()+(q-5), cv.low);
					break;
				case 9:
					roman.push_back(cv.low);
					roman.push_back(cv.high);
					break;
			}
		}
		return roman;
	}
};

int main() {
	Solution s;
	cout << s.intToRoman(3999) << endl;
	cout << s.intToRoman(1954) << endl;
	cout << s.intToRoman(1990) << endl;
	cout << s.intToRoman(2014) << endl;
	for (int i = 1; i <= 20; ++i)
		cout << s.intToRoman(i) << endl;
	return 0;
}
