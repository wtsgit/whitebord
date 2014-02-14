/*
http://oj.leetcode.com/problems/substring-with-concatenation-of-all-words/
Thu Feb 13 18:04:11 EST 2014


Substring with Concatenation of All Words

You are given a string, S, and a list of words, L, that are all of
the same length. Find all starting indices of substring(s) in S
that is a concatenation of each word in L exactly once and without
any intervening characters.

For example, given:
S: "barfoothefoobarman"
L: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

struct DictEntry {
	size_t count, uwid;
};

struct Bucket {
	bool in_use;
	size_t start;
	size_t total_match_count;
	vector<size_t> match_count;
	vector<size_t> first_seen;

	void open(size_t n, size_t start_) {
		in_use = true;
		start = start_;
		total_match_count = 0;
		match_count.clear();
		match_count.resize(n, 0);
		first_seen.clear();
		first_seen.resize(n, 0);
	}
	void close() { in_use = false; }
	Bucket() : in_use(false) {} 
};

class Solution {
public:
	vector<int> findSubstring(string S, vector<string> &L) {
		vector<int> r;
		if (S.size() ==0)
			return r;
		size_t nw = L.size();
		if (nw == 0)
			return r;
		size_t wl = L[0].size();
		if (wl == 0)
			return r;
		unordered_map<string, DictEntry> dict;
		for (const auto &s : L)
			++dict[s].count;
		size_t nuw = 0; // num unique word
		for (auto it = dict.begin(); it != dict.end(); ++it) {
			it->second.uwid = nuw;
			++nuw;
		}
		Bucket bucket;
		for (size_t phase = 0; phase < wl; ++phase) {
			for (size_t i = phase; i+wl-1 < S.size(); ) {
				auto dit = dict.find(S.substr(i, wl));
				if (dit == dict.end()) {
					bucket.close();
				}
				else {
					size_t uwid = dit->second.uwid;
					if (bucket.in_use == false) {
						bucket.open(nuw, i); // start at i
					}
					if (bucket.match_count[uwid] >= dit->second.count) {
						i = bucket.first_seen[uwid] + wl;
						bucket.close();
						continue; // roll back
					}
					if (bucket.match_count[uwid] == 0) {
						bucket.first_seen[uwid] = i;
					}
					bucket.match_count[uwid]++;
					bucket.total_match_count++;
					if (bucket.total_match_count == nw) {
						r.push_back((int)bucket.start);
						i = bucket.start + wl; // roll back
						bucket.close();
						continue;
					}
				}
				i += wl;
			}
			bucket.close();
		}
		std::sort(r.begin(), r.end());
		return r;
	}
};

int main() {
	{
		string S{"barfoothefoobarman"};
		vector<string> L{"foo", "bar"};
		Solution s;
		auto pos = s.findSubstring(S, L);
		for (auto p : pos)
			cout << p << " ";
		cout << endl;
	}
	{
		string S{"aaa"};
		vector<string> L{"aa", "aa"};
		Solution s;
		auto pos = s.findSubstring(S, L);
		for (auto p : pos)
			cout << p << " ";
		cout << endl;
	}
	return 0;
}
