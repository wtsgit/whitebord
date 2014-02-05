/*
http://oj.leetcode.com/problems/word-break-ii/
Sat Jan 4 16:29:06 EST 2014


Word Break II

Given a string s and a dictionary of words dict, add spaces in s
to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
public:
	void listSentences(
			vector<string> &sentences,
			const string &prefix,
			const int start,
			const string &s,
			const vector<vector<int> > &breakable) {
		if (start == s.size()) {
			sentences.push_back(prefix);
			return;
		}
		cout << "start: " << start;
		cout << "  prefix: " << prefix << endl;
		for (size_t i = 0; i < breakable[start].size(); ++i) {
			listSentences(
				sentences,
				prefix == "" ?  s.substr(start, breakable[start][i] - start)
					: prefix + ' ' + s.substr(start, breakable[start][i] - start),
				breakable[start][i],
				s,
				breakable);
		}
	}

	vector<string> wordBreak(string s, unordered_set<string> &dict) {
		size_t n = s.size();
		vector<vector<int> > breakable(n+1);
		breakable[n].push_back(n);
		for (ssize_t i = n-1; i >= 0; --i) {
			for (ssize_t j = i; j <= n-1; ++j) {
				if (dict.find(s.substr(i, j-i+1)) != dict.end() && !breakable[j+1].empty()) {
					breakable[i].push_back(j+1);
				}
			}
		}

		for (size_t i = 0; i < breakable.size(); ++i) {
			cout << i << ": ";
			for (size_t j = 0; j < breakable[i].size(); ++j) {
				cout << breakable[i][j] << " ";
			}
			cout << endl;
		}

		vector<string> sentences;
		listSentences(sentences, "", 0, s, breakable);
		return sentences;
	}

};

int main()
{
	unordered_set<string> dict;
	dict.insert("leet");
	dict.insert("code");
	Solution s;

	vector<string> answer = s.wordBreak("leetcode", dict);
	copy(answer.begin(), answer.end(), ostream_iterator<string>(cout, "\n"));

	dict.clear();
	answer.clear();

	dict.insert("cat");
	dict.insert("cats");
	dict.insert("and");
	dict.insert("sand");
	dict.insert("dog");

	answer = s.wordBreak("catsanddog", dict);
	copy(answer.begin(), answer.end(), ostream_iterator<string>(cout, "\n"));

	return 0;
}
