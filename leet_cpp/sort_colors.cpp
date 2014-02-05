/*
http://oj.leetcode.com/problems/sort-colors/
Thu Jan 23 16:07:48 EST 2014


Sort Colors

Given an array with n objects colored red, white or blue, sort them
so that objects of the same color are adjacent, with the colors in
the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color
red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this
problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using
counting sort.

First, iterate the array counting number of 0's, 1's, and 2's, then
overwrite array with total number of 0's, then 1's and followed by
2's.

Could you come up with an one-pass algorithm using only constant
space?
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	enum {Red=0, White=1, Blue=2};
	void sortColors(int A[], int n) {
		if (n == 0)
			return;
		int *red_zone_end = A;
		int *p = A; // end of first half of sorted array.
		int *blue_zone_start = A+n;
		int *q = A+n; // start of second half of sorted array.
		while (p < q) {
			while (p < q) {
				if (*p == Red) {
					assert(p >= red_zone_end);
					swap(*p, *red_zone_end);
					++red_zone_end;
				}
				else if (*p == Blue) {
					break;
				}
				++p;
			}
			while (p < q) {
				int *t = q-1;
				if (*t == Blue) {
					--blue_zone_start;
					assert(t <= blue_zone_start) ;
					swap(*t, *blue_zone_start);
				}
				else if (*t == Red) {
					break;
				}
				--q;
			}
			if (p < q) {
				// could optimize
				assert(q - p > 1);
				int *t = q-1;
				swap(*t, *p);
			}
		}
	}
};


int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	string s(argv[1]);
	if (s.size() == 0)
		return 1;
	vector<int> vi;
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] == '0')
			vi.push_back(0);
		if (s[i] == '1')
			vi.push_back(1);
		if (s[i] == '2')
			vi.push_back(2);
	}
	int *a = new int[vi.size()];
	copy (vi.begin(), vi.end(), a);
	Solution so;
	so.sortColors(a, vi.size());
	for (size_t i = 0; i < vi.size(); ++i)
		cout << a[i] << " ";
	cout << endl;
	delete [] a;
	return 0;
}
