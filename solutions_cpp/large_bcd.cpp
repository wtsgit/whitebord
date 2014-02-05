#include <cassert>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

class LargeBCD
{
private:
	std::vector<unsigned char> bcd;

public:
	typedef std::vector<unsigned char>::size_type size_type;
	unsigned char & operator[](size_type pos) { return bcd.at(pos); }
	const unsigned char & operator[](size_type pos) const { return bcd.at(pos); }
	size_type size() const { return bcd.size(); }
	

	// Calculate r = (m*n) % (10^k), i.e. last k decimal digits of m^n.
	// We notice that in each step of calculation, only the last k digits
	// matters.  For example, suppose we are calculating 523 * 781 % 100.
	// Notice 523 = 500 + 20 + 3 and 781 = 700 + 80 + 1.  The smallest none
	// zero contribution of 500 in the multiplication is 500 and it does not
	// affect the modulo result.
	// 
	static void mul(LargeBCD &r, const LargeBCD &m, const LargeBCD &n)
	{
		LargeBCD::size_type sz = r.size();
		assert(sz > 0);
		assert(sz == m.size());
		assert(sz == n.size());

		std::fill(r.bcd.begin(), r.bcd.end(), 0);
		for (LargeBCD::size_type i = 0; i < sz; ++i) {
			unsigned int carry = 0;
			for (LargeBCD::size_type j = 0 ; j < sz - i; ++j) {
				assert(i + j < sz);
				unsigned int val = r[i+j] + m[i] * n[j] + carry;
				carry = val / 10;
				r[i+j] = val % 10;
			}
		}
	}

	static void add(LargeBCD &r, unsigned char n)
	{
		LargeBCD::size_type sz = r.size();
		assert(sz > 0);
		assert(n < 10);

		unsigned int carry = n;
		for (LargeBCD::size_type i = 0; i < sz; ++i) {
			unsigned int val = r[i] + carry;
			carry = val / 10;
			r[i] = val % 10;
			if (carry == 0)
				break;
		}
	}

	static void mul(LargeBCD &r, unsigned char n)
	{
		LargeBCD::size_type sz = r.size();
		assert(sz > 0);
		assert(n < 10);

		unsigned int carry = n;
		for (LargeBCD::size_type i = 0; i < sz; ++i) {
			unsigned int val = r[i] * n;
			carry = val / 10;
			r[i] = val % 10;
		}
	}

	static LargeBCD exp(const LargeBCD &m, unsigned long n)
	{
		assert(m.size());

		LargeBCD r_bcd1(m.size());
		if (n & 1) {
			r_bcd1 = m; 
		}
		else {
			r_bcd1[0] = 1;
		}
		LargeBCD *r_val = &r_bcd1;

		LargeBCD r_bcd2(m.size());
		LargeBCD *r_new = &r_bcd2;

		LargeBCD m_sqr_bcd1(m);
		LargeBCD *m_sqr = &m_sqr_bcd1;

		LargeBCD m_sqr_bcd2(m.size());
		LargeBCD *m_sqr_new = &m_sqr_bcd2;

		while (n >>= 1) {
			mul(*m_sqr_new, *m_sqr, *m_sqr);
			std::swap(m_sqr, m_sqr_new);
			if (n & 1) {
				mul(*r_new, *r_val, *m_sqr);
				std::swap(r_new, r_val);
			}
		}

		return *r_val;
	}


	LargeBCD(size_type n) : bcd(n, 0) {}
	LargeBCD(const LargeBCD &n) : bcd(n.bcd) {}

	// Construct LargeBCD from string of decimal digits.
	LargeBCD(size_type sz, const char *str)
	{
		assert(str);
		assert(*str);
		const char *p = str;
		while (*p) {
			if (!isdigit(*p))
				throw std::invalid_argument("Invalid decimal string");
			++p;
		}

		if (sz == 0) {
			sz = p - str;
		}
		else if (sz < p - str) {
			 throw std::invalid_argument("String too long");
		}

		bcd.resize(sz, 0);

		std::vector<unsigned char>::iterator it = bcd.begin();
		while (p != str) {
			*it = *(--p) - '0';
			++it;
		}
	}

	operator std::string () const
	{
		std::string str;
		for (std::vector<unsigned char>::const_reverse_iterator it = bcd.rbegin();
				it != bcd.rend(); ++it) {
			if (*it != 0 || str.size() > 0)
				str.push_back(*it + '0');
		}
		if (str.size() == 0)
			str.push_back('0');
		return str;
	}
};

int test_bcd_exp(int argc, char **argv)
{
	if (argc < 3)
		return 1;

	LargeBCD m(100, argv[1]);
	std::cout << (std::string)LargeBCD::exp(m, atoi(argv[2])) << std::endl;

	return 0;
}

int test_bcd_mul(int argc, char **argv)
{
	if (argc < 3)
		return 1;

	LargeBCD m(8, argv[1]);
	LargeBCD n(8, argv[2]);
	LargeBCD r(8);

	LargeBCD::mul(r, m, n);
	std::cout << (std::string)r << std::endl;

	return 0;
}

int test_bcd_to_string(int argc, char **argv)
{
	if (argc <= 1)
		return 1;

	LargeBCD bcd(100, argv[1]);	
	std::cout << (std::string)bcd << std::endl;

	return 0;
}

int main(int argc, char **argv)
{
	return test_bcd_exp(argc, argv);
	//return test_bcd_mul(argc, argv);
	//return test_bcd_to_string(argc, argv);
}
