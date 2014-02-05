/*
http://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
Sat Jan 11 02:22:25 UTC 2014


Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a
given stock on day i.

Design an algorithm to find the maximum profit. You may complete
at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie,
you must sell the stock before you buy again).
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstddef>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		const size_t n = prices.size();
		if (n <= 1)
			return 0;

		vector<int> trans(n);
		int max_price = 0;
		int max_profit = 0;
		for (ptrdiff_t i = n-1; i >= 0; --i) {
			max_price = max(max_price, prices[i]);
			max_profit = max(max_profit, max_price-prices[i]);
			trans[i] = max_profit;
		}

		int min_price = prices[0];
		max_profit = 0;
		int max_profit_2trans = 0;
		for (size_t i = 0; i < n; ++i) {
			min_price = min(min_price, prices[i]);
			max_profit = max(max_profit, prices[i]-min_price);
			max_profit_2trans = max(max_profit_2trans, trans[i]+max_profit);
		}
		return max_profit_2trans;
	}
};

int main()
{
	return 0;
}
