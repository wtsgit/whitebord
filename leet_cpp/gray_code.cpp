/*
http://oj.leetcode.com/problems/gray-code/
Wed Jan 22 15:59:32 EST 2014


Gray Code

The gray code is a binary numeral system where two successive values
differ in only one bit.

Given a non-negative integer n representing the total number of
bits in the code, print the sequence of gray code. A gray code
sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence
is:

00 - 0
01 - 1
11 - 3
10 - 2

Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according
to the above definition.

For now, the judge is able to judge based on one instance of gray
code sequence. Sorry about that.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <bitset>
#include <cstdlib>

using namespace std;

class Solution {
public:
	vector<int> grayCode(int n) {
		size_t total = (size_t)1 << n;
		vector<int> result(total);
		for (size_t i = 0; i < (size_t)n; ++i) {
			size_t start = (size_t)1 << i;
			size_t j = start;
			size_t k = start;
			while (j > 0) {
				result[k] = result[j-1] | start;
				++k;
				--j;
			}
		}

		return result;
	}
};

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	size_t n = atoi(argv[1]);
	Solution s;
	auto result = s.grayCode(n);
	for (auto x : result)
		cout << bitset<8>(x) << endl;
	return 0;
}
