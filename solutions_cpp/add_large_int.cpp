#include <stdexcept>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cctype>

/*

Add two large integers. Each is represented as sequence of decimal digits.

*/

template <class C>
C add_large_int(const C &c1, const C &c2)
{
	C result;

	typename C::const_iterator p = c1.begin();
	typename C::const_iterator q = c2.begin();
	typename C::const_iterator p_end = c1.end();
	typename C::const_iterator q_end = c2.end();

	if (c1.size() < c2.size()) {
		std::swap(p, q);
		std::swap(p_end, q_end);
	}

	int carry = 0;
	for (; p != p_end; ++p) {
		int i2 = 0;
		if (q != q_end) {
			i2 = *q;
			++q;
		}
		int sum = *p + i2 + carry;
		if (sum >= 10) {
			sum -= 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
		result.push_back(sum);
	}

	if (carry != 0) {
		result.push_back(carry);
	}

	return result;
}

/*

Convert a NULL terminated C string into big integer.

*/

template <class C>
C cstr_to_big_int(const char *str)
{
	if (str == 0)
		throw std::invalid_argument("Null string");

	// Skip all leading spaces.
	const char *p = str;
	while (isspace(*p))
		++p;

	// [start, end) is a substring of decimal digits.
	const char *start = p;
	while (isdigit(*p))
		++p;
	const char *end = p;

	// Skip all trailing spaces.
	while (isspace(*p))
		++p;

	if (*p != '\0')
		throw std::invalid_argument("Bad string");

	if (start == end)
		throw std::invalid_argument("Empty string");

	// Skip all leading zeroes.
	while (*start == '0')
		++start;

	C c;

	if (start == end) {
		c.push_back(0);
	}
	else {
		p = end;
		do
			c.push_back(*--p - '0');
		while (p != start);
	}

	return c;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		return 0;
	}

	std::list<int> lr;
	lr.push_back(0);

	for (int i = 1; i < argc; ++i) {
		try {

			std::list<int> li = cstr_to_big_int<std::list<int> >(argv[i]);
			std::copy(li.rbegin(), li.rend(), std::ostream_iterator<int>(std::cout, ""));
			std::cout << std::endl;
			lr = add_large_int(lr, li);
		}
		catch (const std::exception &e) {
			std::cerr << e.what() << ": " << argv[i] << std::endl;
		}
	}

	std::copy(lr.rbegin(), lr.rend(), std::ostream_iterator<int>(std::cout, ""));
	std::cout << std::endl;

        return 0;
}
