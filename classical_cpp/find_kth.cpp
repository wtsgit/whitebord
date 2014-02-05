#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>
#include "rng.h"
#include "binary_search.h"

//
// k >= 1
//

template <typename C>
typename C::value_type find_kth_merge(size_t k, const C &c1, const C &c2)
{
	if (k < 1)
		throw std::out_of_range("input too small");
	if (k > c1.size() + c2.size())
		throw std::out_of_range("input too large");

	C c3;
	std::merge(c1.begin(), c1.end(), c2.begin(), c2.end(), std::back_inserter(c3));
	return c3[k-1];
}

template <typename IT>
typename std::iterator_traits<IT>::value_type
find_kth_linear(size_t k, IT p, IT p_end, IT q, IT q_end)
{
	if (k < 1)
		throw std::out_of_range("input too small");

	if (p == p_end) {
		std::swap(p, q);
		std::swap(p_end, q_end);
	}

	IT r;
	size_t i;
	for (i = 0; i < k && p != p_end; ++i) {
		if (q == q_end || *p < *q) {
			r = p;
			++p;
			if (p == p_end) {
				std::swap(p, q);
				std::swap(p_end, q_end);
			}
		}
		else {
			r = q;
			++q;
		}
	}

	if (i < k)
		throw std::out_of_range("input too large");

	return *r;
}

template <typename C>
typename C::value_type
find_kth_linear(size_t k, const C &c1, const C &c2) {
	return find_kth_linear(k, c1.begin(), c1.end(), c2.begin(), c2.end());
}

template <typename IT>
typename std::iterator_traits<IT>::value_type
find_kth_binary(size_t k, IT b1, IT e1, IT b2, IT e2) {

	// We count from 1, therefore k > 0.
	if (k < 1)
		throw std::out_of_range("input too small");

	if (e1 - b1 > k)
		e1 = b1 + k;

	if (e2 - b2 > k)
		e2 = b2 + k;

	// If b1 == e1, we only need to find kth element in [b2, e2).
	// If b2 == e2, we only need to find kth element in [b1, e1).
	//
	// For a single sequence, the answer is
	//     *(b + k - 1) if k <= e - b,
	// or
	//     throw error if k > e - b.

	// For iterator pair [b, e):
	//
	//     b + (e - b) / 2 >= b
	//
	// since e >= b therefore floor((e - b) / 2) >= 0.
	//
	// Also:
	//
	//     b + (e - b)/2 <= e
	//
	// since
	//     2 * b + 2 * floor((e - b) / 2)
	//     <= 2 * b + 2 * (e-b) / 2
	//     =  2 * b + e - b
	//     =  e + b
	//     <= 2 * e
	//
	// If e > b, then:
	//
	//     b + (e - b) / 2 < e
	//
	// since e + b < 2 * e in the last step above.

	// Asssume e2 > b2, let
	//     m2 = b2 + (e2 - b2) / 2.
	//
	// Note m2 < e2 and m2 + 1 <= e2
	//
	// Let
	//     t = lower_bound(b1, e1, *m2).
	//
	// If we merge two lists, m2 could appear before before t
	// (t might be e1 but that does not matter).
	//
	// There would be t - b1 elements before m2 from [b1, e1) and
	// m2 - b2 elements before m2 from [b2, e2).
	//
	// m2 would be the (t-b1+m2-b2+1)th element.
	//
	// if (t-b1+m2-b2+1) == k, then m2 is the answer.
	//
	// if (t-b1+m2-b2+1) > k, we reduce the problem to
	//
	//     find_kth(k, b1, t, b2, m2);
	//
	// if (t-b1+m2-b2+1) < k, then we reduce the problem to
	//
	//     find_kth(k - (t-b1+m2-b2+1), t, e1, m2+1, e2);

	while (e1 > b1 && e2 > b2) {
		IT m2 = b2 + (e2 - b2) / 2;
		IT t = wts::lower_bound(b1, e1, *m2);
		size_t m2_rank = t - b1 + m2 - b2 + 1;
		if (m2_rank > k) {
			e1 = t;
			e2 = m2;
		}
		else if (m2_rank < k) {
			b1 = t;
			b2 = m2 + 1;
			k -= m2_rank;
		}
		else
			return *m2;
	}

	IT b = b1;
	IT e = e1;
	if (b1 == e1) {
		b = b2;
		e = e2;
	}

	if (k > (e - b))
		throw std::out_of_range("input too large");

	return *(b + k - 1);
}

template <typename C>
typename C::value_type
find_kth_binary(size_t k, const C &c1, const C &c2) {
	return find_kth_binary(k, c1.begin(), c1.end(), c2.begin(), c2.end());
}

int main(int argc, char **argv)
{
	wts::SimpleRNG<int> rng(1, 100);

	int k = 1;
	if (argc > 1) {
		k = atoi(argv[1]);
	}

	int sv1 = 20;
	if (argc > 2) {
		sv1 = atoi(argv[2]);
	}

	int sv2 = 20;
	if (argc > 3) {
		sv2 = atoi(argv[3]);
	}

	std::vector<int> v1;
	std::vector<int> v2;

	std::generate_n(std::back_inserter(v1), sv1, rng);
	std::generate_n(std::back_inserter(v2), sv2, rng);

	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
	std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	int n;
	try {
		n = find_kth_merge(k, v1, v2);
		std::cout << "merge: " << n << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cerr << "merge: " << e.what() << std::endl;
	}

	try {
		n = find_kth_linear(k, v1, v2);
		std::cout << "linear: " << n << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cerr << "linear: " << e.what() << std::endl;
	}

	try {
		n = find_kth_binary(k, v1, v2);
		std::cout << "binary: " << n << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cerr << "binary: " << e.what() << std::endl;
	}

	return 0;
}
