/*
http://oj.leetcode.com/problems/minimum-window-substring/
Sat Feb  1 20:22:55 EST 2014


Minimum Window Substring

Given a string S and a string T, find the minimum window in S which
will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T,
return the emtpy string "".

If there are multiple such windows, you are guaranteed that there
will always be only one unique minimum window in S.
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	string minWindow(string S, string T) {
		size_t hist[256]{};
		for (auto x : T)
			++hist[(size_t)x];
		size_t found[256]{};
		size_t j = 0;
		size_t wbegin = 0;
		size_t wend = 0;
		size_t wsize = S.size()+1;
		size_t n_found = 0;
		bool has_window = false;
		for (size_t i = 0; i < S.size(); ++i) {
			size_t c = (size_t)S[i];
			if (hist[c] == 0)
				continue;
			if (!has_window) {
				if (found[c] < hist[c])
					++n_found;
				if (n_found == T.size())
					has_window = true;
			}
			++found[c];
			if (has_window) {
				while (true) {
					size_t c = (size_t)S[j];
					if (hist[c] > 0) {
						if (found[c] > hist[c])
							--found[c];
						else
							break;
					}
					++j;
				}

				if (i-j+1 < wsize) {
					wsize = i-j+1;
					wend = i;
					wbegin = j;
				}
			}
		}
		if (has_window)
			return S.substr(wbegin, wend-wbegin+1);
		return string();
	}
};

int main(int argc, char **argv)
{
	if (argc < 3)
		return 1;
	Solution s;
	cout << s.minWindow(argv[1], argv[2]) << endl;
        return 0;
}
