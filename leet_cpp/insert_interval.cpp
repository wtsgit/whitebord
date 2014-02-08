/*
http://oj.leetcode.com/problems/insert-interval/
Thu Feb  6 17:59:04 EST 2014


Insert Interval

Given a set of non-overlapping intervals, insert a new interval into
the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to
their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as
[1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include "leet.h"

using namespace std;

class Solution {
public:
	vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
		vector<Interval> rv;

		auto it = intervals.begin();
		while (it != intervals.end() && it->end < newInterval.start) {
			rv.push_back(*it);
			++it;
		}

		auto s = newInterval.start;
		if (it != intervals.end())
			s = min(s, it->start);

		auto e = newInterval.end;
		while (it != intervals.end() && !(newInterval.end < it->start)) {
			e = max(e, it->end);
			++it;
		}

		rv.emplace_back(s, e);

		while (it != intervals.end()) {
			rv.push_back(*it);
			++it;
		}

		return rv;
	}
};

int main(int argc, char **argv)
{
	if (argc < 3)
		return 1;

	Interval i{atoi(argv[1]), atoi(argv[2])};

	vector<Interval> vi { {3, 4}, {6, 7}, {9, 10}, {12, 12}, {15, 20}, {30, 40}, {51, 52}, {53, 54}, {60, 100} };

	for (auto x : vi) {
		cout << "[" << x.start << "," << x.end << "],";
	}
	cout << endl;

	Solution s;

	auto rv = s.insert(vi, i);
	for (auto x : rv) {
		cout << "[" << x.start << "," << x.end << "],";
	}
	cout << endl;

        return 0;
}
