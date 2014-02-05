/*
http://oj.leetcode.com/problems/search-in-rotated-sorted-array/
Fri Jan 31 21:42:37 EST 2014


Search in Rotated Sorted Array

Suppose a sorted array is rotated at some pivot unknown to you
beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return
its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/

#include <iostream>

using namespace std;


template<class T> struct Accessor {
	T *A;
	const size_t n;
	const size_t start;
	Accessor(T *A, size_t n, size_t start) : A(A), n(n), start(start) {}
	T& operator[](size_t i) const {
		return A[(start+i)%n];
	}
	size_t getOrigIndex(size_t i) const {
		return (start+i)%n;
	}
};

class SolutionOld {
public:
	size_t find_start(int A[], int n) {
		size_t start = 0;
		size_t end = n;
		while (start+1 < end) {
			if (A[start] < A[end-1])
				return start;
			size_t mid = start + (end-start)/2;
			if (A[mid] < A[mid-1])
				return mid;
			if (A[start] < A[mid])
				start = mid+1;
			else
				end = mid;
		}
		return start;
	}

	int search(int A[], int n, int target) {
		if (n == 0)
			return -1;
		Accessor<int> acc(A, n, find_start(A, n));
		size_t start = 0;
		size_t end = n;
		while (start < end) {
			size_t mid = start + (end-start)/2;
			if (acc[mid] == target)
				return acc.getOrigIndex(mid);
			else if (acc[mid] < target)
				start = mid+1;
			else
				end = mid;

		}
		return -1;
	}
};

class Solution {
public:
	int search(int A[], int n, int target) {
		size_t start = 0;
		size_t end = n;
		while (start < end) {
			size_t mid = start + (end-start)/2;
			if (A[mid] == target)
				return mid;
			if (start < mid && A[start] <= A[mid-1]) {
				if (target >= A[start] && target <= A[mid-1])
					end = mid;
				else
					start = mid+1;
			}
			else if (mid+1 < end && A[mid+1] <= A[end-1]) {
				if (target >= A[mid+1] && target <= A[end-1])
					start = mid+1;
				else
					end = mid;
			}
			else {
				return -1;
			}
		}
		return -1;
	}
};

int main()
{
	SolutionOld s;
	constexpr size_t n = 19;
	for (size_t i = 0; i < n; ++i) {
		int A[n];
		Accessor<int> acc(A, n, i);
		for (size_t j = 0; j < n; ++j)
			acc[j] = j+1;
		for (size_t j = 0; j < n; ++j)
			cout << A[j] << " ";
		cout << s.find_start(A, n) << endl;
	}
        return 0;
}

