/*
http://oj.leetcode.com/problems/candy/
Sat Jan  4 21:43:21 EST 2014


Candy

There are N children standing in a line. Each child is assigned a
rating value.

You are giving candies to these children subjected to the following
requirements:

    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give?
*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define MYDEBUG 1

class Solution {
public:
	bool debug_is_on;

	Solution() : debug_is_on(false) {}

	int candy(vector<int> &_ratings) {
		vector<int> ratings(_ratings.size()+2);
		for (size_t i = 0; i < _ratings.size(); ++i)
			ratings[i+1] = _ratings[i];
		ratings[0] = ratings[1];
		ratings[ratings.size()-1] = ratings[ratings.size()-2];

		vector<int> plan(_ratings.size()+2, 1);

		size_t peak;
		bool looking_for_onecandy = false;

		for (size_t i = 1; i < ratings.size()-1; ++i) {
			if (debug_is_on) cout << ratings[i] << ": ";
			if (ratings[i] <= ratings[i-1] && ratings[i] <= ratings[i+1]) {
				/************************************
				 o     o
				  \   /
				o - x - o
				*************************************/
				if (debug_is_on) cout << "onecandy";
				if (looking_for_onecandy) {
					looking_for_onecandy = false;
					for (size_t k = i-1; k > peak; --k) {
						plan[k] =  plan[k+1] + 1;
					}
					plan[peak] = max(plan[peak], plan[peak+1]+1);
				}
			}
			else {
				/*****************************************
				       o
				      /
				    x - o
				   / \
				  o   o
				*****************************************/
				if (ratings[i] > ratings[i-1]) {
					plan[i] = plan[i-1]+1;
				}
				/*****************************************
				 o - x
				    / \
				   o   o
				*****************************************/
				if (ratings[i] > ratings[i+1] && ratings[i] >= ratings[i-1]) {
					looking_for_onecandy = true;
					peak = i;
					if (debug_is_on) cout << "peak";
				}
			}
			if (debug_is_on) cout << endl;
		}
		if (debug_is_on) cout << endl;

		int total = 0;
		for (size_t i = 1; i < plan.size()-1; ++i) {
			if (debug_is_on) cout << ratings[i] << ": " << plan[i] << endl;
			total += plan[i];
		}
		if (debug_is_on) cout << endl;
		return total;
	}
};

int main()
{
	vector<int> ratings;
	Solution s;
	s.debug_is_on = true;

	ratings.push_back(4);
	ratings.push_back(2);
	ratings.push_back(3);
	ratings.push_back(4);
	ratings.push_back(1);
	cout << s.candy(ratings) << endl;

	cout << endl << endl;

	ratings.clear();
	ratings.push_back(1);
	ratings.push_back(2);
	ratings.push_back(4);
	ratings.push_back(4);
	ratings.push_back(3);
	cout << s.candy(ratings) << endl;

	return 0;
}
