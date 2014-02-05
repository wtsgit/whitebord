/*
http://oj.leetcode.com/problems/restore-ip-addresses/
Wed Jan 22 10:46:16 EST 2014


Restore IP Addresses

Given a string containing only digits, restore it by returning all
possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#if defined(__GNUG__) && ! defined(_GLIBCXX_USE_C99)
#include <ext/string_conversions.h>

inline int
stoi(const string& __str, size_t* __idx = 0, int __base = 10)
{ return __gnu_cxx::__stoa<long, int>(&std::strtol, "stoi", __str.c_str(),
	__idx, __base); }
#endif

class Solution {
public:
	bool isByte(string s) {
		if (s.size() == 0)
			return false;
		if (s[0] == '0' && s.size() != 1)
			return false;
		if (s.size() > 3)
			return false;
		if (stoi(s) > 255)
			return false;
		return true;
	}

	void restoreIPSub(vector<string> &coll, string prefix, string s, int n_byte) {
		if (n_byte == 1) {
			if (isByte(s)) {
				prefix += '.';
				prefix += s;
				coll.push_back(prefix);
			}
		}
		else {
			for (size_t i = 1; i <= 3 && i < s.size(); ++i) {
				if (isByte(s.substr(0, i))) {
					auto new_prefix = prefix;
					if (!new_prefix.empty())
						new_prefix += '.';
					new_prefix += s.substr(0, i);
					restoreIPSub(coll, new_prefix, s.substr(i), n_byte-1);
				}
			}
		}
	}

	vector<string> restoreIpAddresses(string s) {
		vector<string> coll;
		restoreIPSub(coll, "", s, 4);
		return coll;
	}
};

int main()
{
	Solution s;
	auto result = s.restoreIpAddresses("0279245587303");
	for (auto x : result)
		cout << x << endl;
	return 0;
}

