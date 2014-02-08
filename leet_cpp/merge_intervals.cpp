/*
http://oj.leetcode.com/problems/merge-intervals/
Sat Feb  8 16:33:32 EST 2014


Merge Intervals

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<Interval> merge(vector<Interval> &intervals) {
		vector<Interval> rv;
		if (intervals.size() == 0)
			return rv;
		sort(intervals.begin(), intervals.end(),
			[](const Interval &a, const Interval &b){ return a.start < b.start; });
		auto it = intervals.begin();
		while (it != intervals.end()) {
			auto start = it->start;
			auto end = it->end;
			while (it != intervals.end() && it->start == start) {
				end = max(end, it->end);
				++it;
			}
			while (it != intervals.end() && end >= it->start) {
				end = max(end, it->end);
				++it;
			}
			rv.emplace_back(start, end);
		}
		return rv;
	}
};

int main(int argc, char **argv)
{
	if (argc < 3)
		return 1;

	vector<Interval> vi { {3, 4}, {6, 7}, {9, 10}, {12, 12}, {15, 20}, {30, 40}, {51, 52}, {53, 54}, {60, 100} };
	vi.emplace_back(atoi(argv[1]), atoi(argv[2]));

	for (auto x : vi) {
		cout << "[" << x.start << "," << x.end << "],";
	}
	cout << endl;

	Solution s;
	auto rv = s.merge(vi);

	for (auto x : rv) {
		cout << "[" << x.start << "," << x.end << "],";
	}
	cout << endl;

;       return 0;
}
