/*
http://oj.leetcode.com/problems/longest-substring-without-repeating-characters/
Mon Feb 17 18:39:00 EST 2014


Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without
repeating characters. For example, the longest substring without
repeating letters for "abcabcbb" is "abc", which the length is 3.
For "bbbbb" the longest substring is "b", with the length of 1.
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.size() == 0)
			return 0;

		vector<bool> chars(256);
		size_t i = 1;
		size_t j = 0;
		size_t len = 1;
		chars[(size_t)s[0]] = true;
		size_t i_longest = 0;
		size_t j_longest = 0;

		while (i < s.size()) {
			if (chars[(size_t)s[i]]) {
				while (s[j] != s[i]) {
					chars[(size_t)s[j]] = false;
					++j;
				}
				++j;
			}
			chars[(size_t)s[i]] = true;
			if (i-j+1 > len) {
				i_longest = i;
				j_longest = j;
			}
			len = max(len, i-j+1);
			++i;
		}
		return (int)len;
	}
};

int main() {
	//string str("arzowkkyhiddqs");
	string str("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco");
	cout << str << endl;
	Solution s;
	cout << s.lengthOfLongestSubstring(str) << endl;
	return 0;
}
