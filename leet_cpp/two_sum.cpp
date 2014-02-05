/*
http://oj.leetcode.com/problems/two-sum/
Tue Aug  6 19:03:25 CST 2013


Two Sum

Given an array of integers, find two numbers such that they add up
to a specific target number.

The function twoSum should return indices of the two numbers such
that they add up to the target, where index1 must be less than
index2. Please note that your returned answers (both index1 and
index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		vector<int> solution(2);

		for (int index1 = 0; index1 < numbers.size(); ++index1) {
			for (int index2 = index1 + 1; index2 < numbers.size(); ++index2) {
				if (numbers[index1] + numbers[index2] == target) {
					solution[0] = index1 + 1;
					solution[1] = index2 + 1;
					return solution;
				}
			}
		}

		solution[0] = -1;
		solution[1] = -1;
		return solution;
	}
};

int main()
{
	vector<int> num = {1, 3, 9, 99, 12, 5, 4};
	Solution solution;
	vector<int> result(2);
	result = solution.twoSum(num, 100);
	cout << result[0] << " " << result[1] << "\n";
	return 0;
}
