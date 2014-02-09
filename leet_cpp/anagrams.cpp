/*
http://oj.leetcode.com/problems/anagrams/
Sun Feb  9 18:00:02 EST 2014


Anagrams

Given an array of strings, return all groups of strings that are
anagrams.

Note: All inputs will be in lower-case.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<string> anagrams(vector<string> &strs) {
		vector<string> r;
		unordered_map<string, vector<string>> mp;
		for (auto &s : strs) {
			string k = s;
			sort(k.begin(), k.end());
			mp[k].push_back(s);
		}
		for (auto it = mp.begin(); it != mp.end(); ++it) {
			if (it->second.size() > 1)
				r.insert(r.end(), it->second.begin(), it->second.end());
		}
		return r;
	}
};

int main()
{
        return 0;
}
