#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/*
Kadane's algorithm for finding maximum subarray.

http://en.wikipedia.org/wiki/Maximum_subarray_problem
*/

typedef pair<int, pair<size_t, size_t> > ret_type;

ret_type max_subarray(const vector<int> &array)
{
	if (array.size() == 0)
		return make_pair(0, make_pair(0, 0));

	int max_ending_here = array[0];
	int max_so_far = array[0];
	size_t begin = 0;
	size_t end = 0;
	size_t begin_tmp = 0;

	for (size_t i = 1; i < array.size(); ++i) {
		if (max_ending_here <= 0) {
			begin_tmp = i;
			max_ending_here = array[i];
		}
		else {
			max_ending_here += array[i];
		}
		if (max_ending_here > max_so_far) {
			max_so_far = max_ending_here;
			begin = begin_tmp;
			end = i+1;
		}
	}

	return make_pair(max_so_far, make_pair(begin, end));
}

int main()
{
        return 0;
}
