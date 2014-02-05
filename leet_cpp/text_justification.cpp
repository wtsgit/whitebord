/*
http://oj.leetcode.com/problems/text-justification/
Mon Feb  3 14:19:51 EST 2014


Text Justification

Given an array of words and a length L, format the text such that
each line has exactly L characters and is fully (left and right)
justified.

You should pack your words in a greedy approach; that is, pack as
many words as you can in each line. Pad extra spaces ' ' when
necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as
possible. If the number of spaces on a line do not divide evenly
between words, the empty slots on the left will be assigned more
spaces than the slots on the right.

For the last line of text, it should be left justified and no extra
space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:

[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Note: Each word is guaranteed not to exceed L in length.
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	vector<string> fullJustify(vector<string> &words, int L) {
		vector<string> result;
		size_t start = 0;
		size_t end = 0;
		size_t lw = 0;
		size_t n = 0;
		while (start < words.size()) {
			const string &s = words[end];
			lw += s.size(); ++n;
			size_t llen = lw + n-1;
			if (llen > (size_t)L || end == words.size()-1) {
				if (llen > (size_t)L) {
					lw -= s.size();
					--n;
					llen = lw + n-1;
					--end;
				}
				size_t nspace = (size_t)L - lw;
				size_t gap = 0;
				size_t extra = nspace;
				size_t trailing = 0;
				if (end == words.size()-1) {
					gap = 1;
					extra = 0;
					trailing = nspace - (n-1)*gap;
				}
				else if (n > 1) {
					gap = nspace/(n-1);
					extra = nspace % (n-1);
				}
				result.emplace_back();
				string &line = result.back();
				for (size_t i = start; i <= end; ++i) {
					line += words[i];
					if (i != end) {
						line += string(gap, ' ');
						if (extra > 0) {
							line += ' ';
							--extra;
						}
					}
				}
				if (extra+trailing > 0)
					line += string(extra+trailing, ' ');
				lw = 0; n = 0;
				++end;
				start = end;
			}
			else {
				++end;
			}
		}
		return result;
	}
};

int main()
{
	Solution s;
	vector<string> words{"This", "is", "an", "example", "of", "text", "justification."};
	auto result = s.fullJustify(words, 16);
	for (auto &s : result) {
		cout << '"' << s << '"'; cout << endl;
	}
	words = {"What","must","be","shall","be."};
	result = s.fullJustify(words, 12);
	for (auto &s : result) {
		cout << '"' << s << '"'; cout << endl;
	}
        return 0;
}
