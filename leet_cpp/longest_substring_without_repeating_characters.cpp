/*
http://oj.leetcode.com/problems/longest-substring-without-repeating-characters/
Tue Aug  6 19:25:55 CST 2013


Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without
repeating characters. For example, the longest substring without
repeating letters for "abcabcbb" is "abc", which the length is 3.
For "bbbbb" the longest substring is "b", with the length of 1.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		// brutal force
		int answer = 0;
		for (int i = 0; i < s.size(); ++i) {
			vector<bool> seen(256);
			for (int k = 0; k < 256; ++k) {
				seen[k] = false;
			}
			int new_answer = 0;
			for (int j = i; j < s.size(); ++j) {
				if (seen[s[j]]) {
					break;
				}
				else {
					seen[s[j]] = true;;
					++new_answer;
				}
			}
			if (new_answer > answer) {
				answer = new_answer;
			}
		}

		return answer;
	}
};

class Solution2 {
public:
	int lengthOfLongestSubstring(string s) {
		int lastSeen[256];
		int i;
		for (i = 0; i < 256; ++i) {
			lastSeen[i] = -1;
		}
		int max_len = 0;
		int start = 0;
		for (i = 0; i < s.size(); ++i) {
			char c = s[i];
			if (lastSeen[c] >= start) {
				if (i - start > max_len) {
					max_len = i - start;
				}
				start = lastSeen[c] + 1;
			}
			lastSeen[c] = i;
		}
		if (i - start > max_len) {
			max_len = i - start;
		}
		return max_len;
	}
};

int main() {
	Solution sol1;
	Solution2 sol2;
	vector<string> vs;
	vs.push_back("");
	vs.push_back("s");
	vs.push_back("ss");
	vs.push_back("sk");
	vs.push_back("skj");
	vs.push_back("sks");
	vs.push_back("skk");
	vs.push_back("skk1234567890");
	for (vector<string>::iterator it = vs.begin(); it != vs.end(); ++it) {
		cout << *it << ": " << "sol1 = " << sol1.lengthOfLongestSubstring(*it) << "\n";
		cout << *it << ": " << "sol2 = " << sol2.lengthOfLongestSubstring(*it) << "\n";
	}

	return 0;
}
