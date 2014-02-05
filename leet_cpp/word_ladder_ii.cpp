/*
http://oj.leetcode.com/problems/word-ladder-ii/
Wed Jan  8 19:06:23 EST 2014


Word Ladder II

Given two words (start and end), and a dictionary, find all shortest
transformation sequence(s) from start to end, such that:

    Only one letter can be changed at a time
    Each intermediate word must exist in the dictionary

For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]

Return

  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]

Note:

    All words have the same length.
    All words contain only lowercase alphabetic characters.
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <string>
#include <climits>

using namespace std;

class SetCompare {
public:
	bool operator()(const pair<int, const string *> &a, const pair<int, const string *> &b) {
		return a.first < b.first;
	}
};

class StringHashThruPtr {
public:
	typedef std::size_t result_type;
	result_type operator()(const string *s) const {
		std::hash<string> h;
		return h(*s);
	}
};

class StringEqThruPtr {
public:
	bool operator()(const string *s1, const string *s2) const {
		if (s1 == s2)
			return true;
		if (s1 && s2)
			return *s1 == *s2;
		return false;
	}
};

class Solution {
public:
	typedef list<const string *> NeighborList;
	typedef unordered_map<string, NeighborList> NeighborMap;
	typedef multiset<pair<int, const string *>, SetCompare> QueueForUnmarked;
	typedef unordered_map<const string *, int, StringHashThruPtr, StringEqThruPtr> WordDistMap;
	typedef unordered_map<const string *, NeighborList, StringHashThruPtr, StringEqThruPtr> WordPathMap;

	void getLadders(vector<vector<string > > &coll,
			const vector<string> &prefix,
			const string &word,
			const string &start,
			const WordPathMap &word_path) {

		vector<string> new_prefix(prefix);
		new_prefix.push_back(word);
		if (word == start) {
			coll.push_back(new_prefix);
			return;
		}
		WordPathMap::const_iterator it = word_path.find(&word);
		if (it != word_path.end()) {
			const NeighborList &nl = it->second;
			for (NeighborList::const_iterator it = nl.begin(); it != nl.end(); ++it) {
				getLadders(coll, new_prefix, **it, start, word_path);
			}
		}
	}

	vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
		NeighborMap neighbors;
		QueueForUnmarked unmarked;
		WordDistMap word_dist;
		WordPathMap word_path;
		string pat;
		dict.insert(start);
		dict.insert(end);
		for (unordered_set<string>::const_iterator dit = dict.begin(); dit != dict.end(); ++dit) {
			const string &word = *dit;
			pat = word;
			for (size_t i = 0; i < word.size(); ++i) {
				char c = pat[i];
				pat[i] = '$';
				NeighborMap::iterator nit = neighbors.find(pat);
				if (nit != neighbors.end()) {
					nit->second.push_back(&word);
				}
				else {
					neighbors[pat] = NeighborList(1, &word);
				}
				pat[i] = c;
			}
			if (word != end) {
				unmarked.insert(pair<int, const string *>(INT_MAX-1, &word));
				word_dist[&word] = INT_MAX-1;
			}
			else {
				unmarked.insert(pair<int, const string *>(1, &word));
				word_dist[&word] = 1;
			}
		}

		while (!unmarked.empty()) {
			const string &word = *unmarked.begin()->second;
			int dist = unmarked.begin()->first;
			for (size_t i = 0; i < word.size(); ++i) {
				pat = word;
				char c = pat[i];
				pat[i] = '$';
				NeighborMap::iterator nit = neighbors.find(pat);
				pat[i] = c;
				if (nit != neighbors.end()) {
					NeighborList &nl = nit->second;
					for (NeighborList::iterator nlit = nl.begin(); nlit != nl.end(); ++nlit) {
						const string *neighbor = *nlit;
						int neighbor_dist = word_dist[neighbor];
						if (dist+1 < neighbor_dist) {
							word_dist[neighbor] = dist+1;
							word_path[neighbor] = NeighborList(1, &word);
							unmarked.erase(make_pair(neighbor_dist, neighbor));
							unmarked.insert(make_pair(dist+1, neighbor));
						}
						else if (dist+1 == neighbor_dist) {
							word_path[neighbor].push_back(&word);
						}
					}
				}
			}
			unmarked.erase(unmarked.begin());
		}

		vector<vector<string> > coll;
		getLadders(coll, vector<string>(), start, end, word_path);
		return coll;
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
	vector<vector<string> > result = s.findLadders("hit", "cog", dict);
	for (vector<vector<string> >::iterator it = result.begin(); it != result.end(); ++it) {
		for (vector<string>::iterator wit = it->begin(); wit != it->end(); ++wit) {
			cout << *wit << " ";
		}
		cout << endl;
	}

	return 0;
}
