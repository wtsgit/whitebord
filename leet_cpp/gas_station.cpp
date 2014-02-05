/*
http://oj.leetcode.com/problems/gas-station/
Sun Jan  5 17:30:22 EST 2014


Gas Station

There are N gas stations along a circular route, where the amount
of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of
gas to travel from station i to its forward station (i+1). You begin
the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around
the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.
*/
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
	bool debug_on;
	Solution() : debug_on(false) {}

	int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
		size_t n = gas.size();
		assert(n > 0);
		assert(n == cost.size());

		size_t start = 0;
		size_t car = start;
		int tank = 0;
		while (true) {
			tank += gas[car] - cost[car];
			++car;
			if (car >= n)
				car -= n;
			if (debug_on) cout << "start:" << start << " car: " << car << " tank: " << tank << endl;
			if (tank < 0) {
				if (car <= start)
					return -1;
				start = car;
				tank = 0;
				continue;
			}
			if (car == start)
				break;
		}
		return start;
	}
};


int main()
{
	vector<int> gas;
	vector<int> cost;

	gas.push_back(2);
	gas.push_back(4);
	cost.push_back(3);
	cost.push_back(4);

	Solution s;
	s.debug_on = true;
	cout << s.canCompleteCircuit(gas, cost) << endl;

	return 0;
}
