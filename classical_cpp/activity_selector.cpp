#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

template<typename T>
void recursive_activity_select(
	vector<T>& ret,
	const vector<T>& s,
	const vector<T>& f,
	size_t k)
{
	assert(s.size() == f.size());
	assert(k >= 0);
	assert(k < s.size());
	size_t i;
	for (i = k+1; i < s.size() && s[i] < f[k]; ++i) {
		// nop
	}
	if (i < s.size()) {
		ret.push_back(i);
		recursive_activity_select(ret, s, f, i);
	}
}

template<typename T>
void iterative_activity_select(
	vector<T>& ret,
	const vector<T>& s,
	const vector<T>& f)
{
	assert(s.size() == f.size());
	for (size_t k = 0, i = 1; i < s.size(); ++i) {
		if (s[i] >= f[k]) {
			ret.push_back(i);
			k = i;
		}
	}
}


int main()
{
	vector<int> s;
	vector<int> f;
	s.push_back(0);
	f.push_back(0);
	s.push_back(1);
	f.push_back(4);
	s.push_back(3);
	f.push_back(5);
	s.push_back(0);
	f.push_back(5);
	s.push_back(5);
	f.push_back(7);
	s.push_back(3);
	f.push_back(9);
	s.push_back(5);
	f.push_back(9);
	s.push_back(6);
	f.push_back(10);
	s.push_back(8);
	f.push_back(11);
	s.push_back(8);
	f.push_back(12);
	s.push_back(2);
	f.push_back(14);
	s.push_back(12);
	f.push_back(16);

	vector<int> sol;
	recursive_activity_select<int>(sol, s, f, 0);
	for (vector<int>::const_iterator it = sol.begin(); it != sol.end(); ++it) {
		cout << setw(4) << *it;
	}
	cout << endl;

	sol.clear();
	iterative_activity_select<int>(sol, s, f);
	for (vector<int>::const_iterator it = sol.begin(); it != sol.end(); ++it) {
		cout << setw(4) << *it;
	}
	cout << endl;

        return 0;
}
