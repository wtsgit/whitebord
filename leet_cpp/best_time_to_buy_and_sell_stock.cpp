/*
http://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock/
Sat Jan 11 01:07:41 UTC 2014


Best Time to Buy and Sell Stock

Say you have an array for which the ith element is the price of a
given stock on day i.

If you were only permitted to complete at most one transaction (ie,
buy one and sell one share of the stock), design an algorithm to
find the maximum profit.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		if (prices.size() == 0)
			return 0;
		int min_price = prices[0];
		int max_profit = 0;
		for (size_t i = 0; i < prices.size(); ++i) {
			min_price = min(min_price, prices[i]);
			max_profit = max(max_profit, prices[i]-min_price);
		}
		return max_profit;
	}
};

int main()
{
	return 0;
}
