/*
http://oj.leetcode.com/problems/word-ladder/
Wed Jan  8 19:06:23 EST 2014


Word Ladder

Given two words (start and end), and a dictionary, find the length
of shortest transformation sequence from start to end, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the dictionary

For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:

    Return 0 if there is no such transformation sequence.
    All words have the same length.
    All words contain only lowercase alphabetic characters.
*/

#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

class SetCompare {
public:
	bool operator()(const pair<int, string> &a, const pair<int, string> &b) {
		return a.first < b.first;
	}
};

class Solution {
public:
	typedef unordered_multimap<string, string> NeighborMap;
	typedef multiset<pair<int, string>, SetCompare> QueueForUnmarked;
	typedef unordered_map<string, int> WordDistMap;

	int ladderLength(string start, string end, unordered_set<string> &dict) {
		NeighborMap neighbors;
		QueueForUnmarked unmarked;
		WordDistMap word_dist;
		string pat;
		dict.insert(start);
		dict.insert(end);
		for (unordered_set<string>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
			pat = *it;
			for (size_t i = 0; i < it->size(); ++i) {
				char c = pat[i];
				pat[i] = '$';
				neighbors.insert(make_pair(pat, *it));
				pat[i] = c;
			}
			if (*it != start) {
				unmarked.insert(make_pair(INT_MAX-1, *it));
				word_dist[*it] = INT_MAX-1;
			}
			else {
				unmarked.insert(make_pair(1, *it));
				word_dist[*it] = 1;
			}
		}

		while (!unmarked.empty()) {
			const string &word = unmarked.begin()->second;
			int dist = unmarked.begin()->first;
			for (size_t i = 0; i < word.size(); ++i) {
				pat = word;
				char c = pat[i];
				pat[i] = '$';
				pair<NeighborMap::const_iterator, NeighborMap::const_iterator> eq_range
					= neighbors.equal_range(pat);
				NeighborMap::const_iterator bit = eq_range.first;
				NeighborMap::const_iterator eit = eq_range.second;
				pat[i] = c;
				for (NeighborMap::const_iterator it = bit; it != eit; ++it) {
					const string &neighbor = it->second;
					int neighbor_dist = word_dist[neighbor];
					if (dist+1 < neighbor_dist) {
						word_dist[neighbor] = dist+1;
						unmarked.erase(make_pair(neighbor_dist, neighbor));
						unmarked.insert(make_pair(dist+1, neighbor));
					}
				}
			}
			unmarked.erase(unmarked.begin());
		}

		if (word_dist[end] == INT_MAX-1)
			return 0;
		return word_dist[end];
	}
};

int main()
{
	unordered_set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("lot");
	dict.insert("log");
	Solution s;
	cout << s.ladderLength("hit", "cog", dict) << endl;
	return 0;
}
