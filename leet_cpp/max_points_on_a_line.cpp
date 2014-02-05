/*
http://oj.leetcode.com/problems/max-points-on-a-line/
Wed Dec 18 19:35:42 EST 2013


Max Points on a Line

Given n points on a 2D plane, find the maximum number of points
that lie on the same straight line.
*/

#include <map>
#include <vector>
#include <iostream>
#include "leet.h"

using namespace std;

struct PointCompare {
	bool operator()(const Point &a, const Point &b) const
	{
		return ((a.x < b.x) || ((a.x == b.x) && (a.y < b.y)));
	}
};

class Solution {
public:
	typedef double Slope;

	typedef map<Point, int, PointCompare> PointSet;

	Slope calc_slope(const Point &p, const Point &q)
	{
		if (q.x == p.x)
			return 1.0/0.0;

		return (q.y - p.y)/(double)(q.x - p.x);
	}

	int max_points_with_i(const PointSet &point_set, const PointSet::const_iterator p)
	{
		typedef map<Slope, int> Counter;
		int max = p->second;
		Counter count;
		PointSet::const_iterator q = p;
		++q;
		for (; q != point_set.end(); ++q) {
			Slope slope = calc_slope(p->first, q->first);
			pair<Counter::iterator, bool> ret;
			ret = count.insert(make_pair(slope, p->second + q->second));
			if (!ret.second)
				ret.first->second += q->second;
			if (ret.first->second > max)
				max = ret.first->second;
		}
		return max;
	}

	PointSet make_point_set(const vector<Point> &points)
	{
		PointSet point_set;
		for (vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it) {
			pair<PointSet::iterator, bool> ret;
			ret = point_set.insert(make_pair(*it, 1));
			if (!ret.second)
				++(ret.first->second);
		}
		return point_set;
	}

	int maxPoints(vector<Point> &points) {
		// For each point p, check all line segments originating from p.

		int max = 0;
		PointSet point_set = make_point_set(points);

		for (PointSet::const_iterator it = point_set.begin(); it != point_set.end(); ++it) {
			int max_i = max_points_with_i(point_set, it);
			if (max_i > max)
				max = max_i;
		}
		return max;
	}
};

int main()
{
	vector<Point> points;

	points.push_back(Point(0,-12));
	points.push_back(Point(5,2));
	points.push_back(Point(2,5));
	points.push_back(Point(0,-5));
	points.push_back(Point(1,5));
	points.push_back(Point(2,-2));
	points.push_back(Point(5,-4));
	points.push_back(Point(3,4));
	points.push_back(Point(-2,4));
	points.push_back(Point(-1,4));
	points.push_back(Point(0,-5));
	points.push_back(Point(0,-8));
	points.push_back(Point(-2,-1));
	points.push_back(Point(0,-11));
	points.push_back(Point(0,-9));

	Solution sol;
	cout << sol.maxPoints(points) << endl;

	return 0;
}
