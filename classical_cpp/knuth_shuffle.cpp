#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec(10);
	const size_t n = vec.size();
	random_device rd;
	default_random_engine rng(rd());
	uniform_int_distribution<size_t> urand(0, n);
	// TBD
        return 0;
}
