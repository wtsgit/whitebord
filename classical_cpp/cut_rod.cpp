//
// CLRS - Introduction to Algorithms 3rd Ed.
// 	15.1 Rod Cutting
//	Recursive top-down implementation
//
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <limits>
#include <cassert>
#include <iomanip>
#include <sys/time.h>

using namespace std;

class CutRod {
private:
	struct timeval tp0;
	struct timeval tp1;
	size_t call_count;
	const vector<int> &p;
public:
	CutRod(const vector<int> &p_) : p(p_) {}

	void start() {
		gettimeofday(&tp0, 0);
		call_count = 0;
	}

	void stop() {
		gettimeofday(&tp1, 0);
	}

	size_t get_call_count() {
		return call_count;
	}

	double get_time_cost() {
		return tp1.tv_sec - tp0.tv_sec
			+ 1e-6 * (tp1.tv_usec - tp0.tv_usec);
	}

	typedef int (CutRod::*algorithm)(const vector<int> &, int);

	void test(algorithm algo, int n) {
		assert (n >= 1);
		for (int i = 1; i <= n; ++i) {
			start();
			int ret = (this->*algo)(p, i);
			stop();
			cout << setw(2) << i << ": " << ret;
			cout << "\t" << get_call_count() << " calls, ";
			cout << get_time_cost() << " seconds\n";
		}
	}

	// Recursive Top-Down Algorithm
public:
	int recursive_top_down(const vector<int> &p, int n) {
		assert(n <= (p.size() - 1));
		++call_count;
		if (n == 0)
			return 0;
		int q = numeric_limits<int>::min();
		for (int i = 1; i <= n; ++i) {
			q = max(q, p[i] + recursive_top_down(p, (n - i)));
		}
		return q;
	}

	// Memoization Algorithm
private:
	int memoized_aux(const vector<int> &p, int n, vector<int> &r) {
		++call_count;
		assert(n <= p.size()-1);
		assert(n <= r.size()-1);
		if (r[n] >= 0)
			return r[n];
		int q;
		if (n == 0) {
			q = 0;
		}
		else {
			q = numeric_limits<int>::min();
			for (int i = 1; i <= n; ++i)
				q = max(q, p[i] + memoized_aux(p, (n - i), r));
		}
		r[n] = q;
		return q;
	}
public:
	int memoized(const vector<int> &p, int n) {
		++call_count;
		vector<int> r((n + 1), numeric_limits<int>::min());
		return memoized_aux(p, n, r);
	}

	// Bottom-Up Algorithm
public:
	int bottom_up(const vector<int> &p, int n) {
		assert(n >= 1);
		assert(n <= (p.size() - 1));
		++call_count;
		vector<int> r((n + 1), 0);
		for (int j = 1; j <= n; ++j) {
			int q = numeric_limits<int>::min();
			for (int i = 1; i <= j; ++i)
				q = max(q, p[i] + r[j - i]);
			r[j] = q;
		}
		return r[n];
	}

	// Extended Bottom-Up Algorithm
public:
	void extended_bottom_up(vector<int> &r, vector<int> &s,
			const vector<int> &p, int n) {
		assert(n >= 1);
		assert(n <= (p.size() -1));
		r.clear();
		s.clear();
		r.resize((n+1), 0);
		s.resize((n+1));
		for (int j = 1; j <= n; ++j) {
			int q = numeric_limits<int>::min();
			for (int i = 1; i <= j; ++i) {
				if (q < p[i] + r[j - i]) {
					q = p[i] + r[j - i];
					s[j] = i;
				}
			}
			r[j] = q;
		}
	}

	void generate_cut_rod_solution(vector<int> &cuts,
			const vector<int> &s, int n) {
		assert(n >= 1);
		assert(n <= (s.size() - 1));
		cuts.clear();
		while (n > 0) {
			cuts.push_back(s[n]);
			n = n - s[n];
		}
	}
};

int main() {
	vector<int> p;

	p.push_back(0);
	p.push_back(1);
	p.push_back(5);
	p.push_back(8);
	p.push_back(9);
	p.push_back(10);
	p.push_back(17);
	p.push_back(17);
	p.push_back(20);
	p.push_back(24);

	for (int i = p.size(); i < 32; ++i) {
		p.push_back(20 + i);
	}

	CutRod cutrod(p);

	cout << "\n\n**** Recursive Top-Down ****\n\n";
	cutrod.test(&CutRod::recursive_top_down, 25);

	cout << "\n\n**** Memoized ****\n\n";
	cutrod.test(&CutRod::memoized, 25);

	cout << "\n\n**** Bottom-Up ****\n\n";
	cutrod.test(&CutRod::bottom_up, 25);

	cout << "\n\n**** Extended Bottom-Up ****\n\n";
	vector<int> r;
	vector<int> s;
	vector<int> cuts;
	for (int i = 1; i <= 25; ++i) {
		cutrod.extended_bottom_up(r, s, p, i);
		assert (i <= r.size() - 1);
		cout << setw(2) << i << ": price=" << r[i];
		cout << ", cut points=";
		cutrod.generate_cut_rod_solution(cuts, s, i);
		copy(cuts.begin(), cuts.end(),
			ostream_iterator<int>(cout, ", "));
		cout << "\n";
	}

        return 0;
}
