/*
http://oj.leetcode.com/problems/longest-consecutive-sequence/
Tue Jan  7 14:40:13 EST 2014


Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest
consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return
its length: 4.

Your algorithm should run in O(n) complexity.
*/

#include <iostream>
#include <unordered_set>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

struct Seq {
	int start;
	int len;
	Seq(int s, int l) : start(s), len(l) {}
};

class Solution {
private:
public:
	bool debug_on;
	Solution() : debug_on(false) {}

	int longestConsecutive(vector<int> &num) {
		unordered_set<int> s;
		for (vector<int>::iterator it = num.begin(); it != num.end(); ++it) {
			s.insert(*it);
		}
		int max_len = 0;
		int start = 0;
		while (!s.empty()) {
			int i = *s.begin();
			start = i;
			int len = 1;
			s.erase(i);
			int j = i-1;
			while (s.find(j) != s.end()) {
				s.erase(j);
				start = j;
				++len;
				--j;
			}
			j = i+1;
			while (s.find(j) != s.end()) {
				s.erase(j);
				++len;
				++j;
			}
			if (len > max_len) {
				max_len = len;
			}
		}
		if (debug_on) cout << "start: " << start << ", len: " << max_len << endl;
		return max_len;
	}

	int longestConsecutiveBySorting(vector<int> &num) {
		if (num.size() == 0) {
			return 0;
		}
		sort(num.begin(), num.end());
		int start = num[0];
		int len = 1;
		int new_start = start;
		int new_len = len;
		for (int i = 1; i < num.size(); ++i) {
			if (num[i-1]+1 == num[i]) {
				++new_len;
				if (new_len > len) {
					start = new_start;
					len = new_len;
				}
			}
			else if (num[i-1] != num[i]) {
				new_start = num[i];
				new_len = 1;
			}
		}

		if (debug_on) {
			copy(num.begin(), num.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			cout << "start: " << start << " " << "len: " << len << endl;
		}

		return len;
	}
};

int main(int argc, char **argv)
{
	if (argc <= 1)
		return 0;
	stringstream ss;
	for (int i = 1; i < argc; ++i)
		ss << argv[i] << " ";
	vector<int> v;
	while (ss) {
		int i;
		ss >> i;
		if (ss) v.push_back(i);
	}

	Solution s;
	s.debug_on = true;

	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	//cout << s.longestConsecutiveBySorting(v) << endl;
	cout << s.longestConsecutive(v) << endl;

	return 0;
}
