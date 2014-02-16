/*
http://oj.leetcode.com/problems/letter-combinations-of-a-phone-number/
Sat Feb 15 18:54:01 EST 2014


Letter Combinations of a Phone Number

Given a digit string, return all possible letter combinations that
the number could represent.

A mapping of digit to letters (just like on the telephone buttons)
is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer
could be in any order you want.
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

using namespace std;

class Solution {
private:
	unordered_map<char, string> mp;

public:
	Solution() {
		mp['2'] = "abc";
		mp['3'] = "def";
		mp['4'] = "ghi";
		mp['5'] = "jkl";
		mp['6'] = "mno";
		mp['7'] = "pqrs";
		mp['8'] = "tuv";
		mp['9'] = "wxyz";
	}

	void helper(vector<string> &r, string s, string digits) {
		if (digits.size() == 0) {
			r.push_back(s);
			return;
		}
		char c = digits[0];
		digits.erase(digits.begin());
		if (mp.find(c) == mp.end())
			throw std::invalid_argument("Invalid digit");
		for (auto ch : mp[c])
			helper(r, s+ch, digits);
	}

	vector<string> letterCombinations(string digits) {
		vector<string> r;
		helper(r, "", digits);
		return r;
	}
};

int main() {
	Solution s;
	auto vs = s.letterCombinations("23");
	for (auto s : vs)
		cout << s << endl;
	return 0;
}
