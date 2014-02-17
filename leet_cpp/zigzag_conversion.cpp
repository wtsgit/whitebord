/*
http://oj.leetcode.com/problems/zigzag-conversion/
Sun Feb 16 20:00:44 EST 2014


ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a
given number of rows like this: (you may want to display this pattern
in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion
given a number of rows:

string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	string convert(string s, int nRows) {
		if (nRows <= 1)
			return s;
		vector<string> vs(nRows);
		for (size_t i = 0; i < s.size(); ++i) {
			size_t q = i / (size_t)(nRows-1);
			size_t row = i % (nRows-1);
			if (q & 1)
				row = (size_t)nRows-1 - i%(size_t)(nRows-1);
			vs[row].push_back(s[i]);
		}
		string rs;
		for (auto &s : vs)
			rs += s;
		return rs;
	}
};

int main() {
	Solution s;
	cout << s.convert("PAYPALISHIRING", 3) << endl;
	return 0;
}
