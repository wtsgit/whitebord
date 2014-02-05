#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

class LargeInt {
public:
	typedef unsigned char u_basic_int;
	typedef unsigned short u_extended_int;
	typedef std::vector<u_basic_int>::size_type size_type;

private:
	std::vector<u_basic_int> buf;

public:
	u_basic_int & operator[](size_type pos) { return buf.at(pos); }
	const u_basic_int & operator[](size_type pos) const { return buf.at(pos); }
	size_type size() const { return buf.size(); }

	// Calculate r = (m*n) % (2^k), i.e. last k biniary digits of m^n.
	// We notice that in each step of calculation, only the last k digits
	// matters.
	// 
	static void mul(LargeInt &r, const LargeInt &m, const LargeInt &n)
	{
		LargeInt::size_type sz = r.size();
		assert(sz > 0);
		assert(sz == m.size());
		assert(sz == n.size());

		std::fill(r.buf.begin(), r.buf.end(), 0);
		for (LargeInt::size_type i = 0; i < sz; ++i) {
			u_extended_int carry = 0;
			for (LargeInt::size_type j = 0 ; j < sz - i; ++j) {
				u_extended_int val
					= (u_extended_int)r[i+j] +
					  (u_extended_int)m[i] * (u_extended_int)n[j] +
					  carry;
				carry = val >> (sizeof(u_basic_int)*8);
				r[i+j] = val & ((u_extended_int)~(u_basic_int)0);
			}
		}
	}

	static void add(LargeInt &r, const LargeInt &m, const LargeInt &n)
	{
		LargeInt::size_type sz = r.size();
		assert(sz > 0);
		assert(sz == m.size());
		assert(sz == n.size());

		u_extended_int carry = 0;
		for (LargeInt::size_type i = 0; i < sz; ++i) {
			u_extended_int val
				= (u_extended_int)m[i] +
				  (u_extended_int)n[i] +
				  carry;
			carry = val >> (sizeof(u_basic_int)*8);
			r[i] = val & ((u_extended_int)~(u_basic_int)0);
		}
	}

	static void mul_int(LargeInt &r, const u_basic_int k)
	{
		LargeInt::size_type sz = r.size();
		assert(sz > 0);
		u_extended_int carry = 0;
		for (LargeInt::size_type i = 0; i < sz; ++i) {
			u_extended_int val
				= (u_extended_int)r[i] * (u_extended_int)k
				  + carry;
			carry = val >> (sizeof(u_basic_int)*8);
			r[i] = val & ((u_extended_int)~(u_basic_int)0);
		}
	}

	static void add_int(LargeInt &r, const u_basic_int k)
	{
		LargeInt::size_type sz = r.size();
		assert(sz > 0);
		u_extended_int carry = k;
		for (LargeInt::size_type i = 0; i < sz; ++i) {
			u_extended_int val = (u_extended_int)r[i] + carry;
			carry = val >> (sizeof(u_basic_int)*8);
			r[i] = val & ((u_extended_int)~(u_basic_int)0);
			if (carry == 0)
				break;
		}
	}

	static void exp(LargeInt &r, const LargeInt &m, size_type n)
	{
		assert(r.size());
		assert(m.size());
		assert(r.size() == m.size());

		LargeInt r_buff1(r.size());
		LargeInt r_buff2(r.size());

		if (n & 1) {
			r_buff1.buf = m.buf; 
		}
		else {
			r_buff1[0] = 1;
		}

		LargeInt *r_val = &r_buff1;
		LargeInt *r_new = &r_buff2;

		LargeInt m_sqr_buff1(m);
		LargeInt *m_sqr = &m_sqr_buff1;

		LargeInt m_sqr_buff2(r.size());
		LargeInt *m_sqr_new = &m_sqr_buff2;

		while (n >>= 1) {
			mul(*m_sqr_new, *m_sqr, *m_sqr);
			std::swap(m_sqr, m_sqr_new);
			if (n & 1) {
				mul(*r_new, *r_val, *m_sqr);
				std::swap(r_new, r_val);
			}
		}

		r = *r_val;
	}

	// Given an integer with n decimal digits, estimate how many u_basic_int are needed
	// represent it.
	//
	static size_type estimate_size(const size_type n)
	{
		// The maximum number with n decimal digits is 10^n - 1.
		// The maxinum number with k binary digits is 2^k - 1.
		// 2^k - 1 >= 10^n - 1
		// 2^k >= 10^n
		// k >= n log 10
		return (size_type)(n * log(10.0)/log(2.0) + 1);
	}

	LargeInt(size_type n) : buf(n, 0) {}
	LargeInt(const LargeInt &n) : buf(n.buf) {}

	// Construct LargeInt from string of decimal digits.
	LargeInt(const char *str, size_type sz = 0)
	{
		if (str == 0 || *str == 0) {
			throw std::invalid_argument("Invalid decimal string");
		}

		const char *p = str;
		while (*p) {
			if (!isdigit(*p))
				throw std::invalid_argument("Invalid decimal string");
			++p;
		}

		if (sz == 0) {
			sz = estimate_size((p - str));
		}
		else if (estimate_size((p - str)) > sz) {
			throw std::invalid_argument("String too long");
		}

		buf.resize(sz, 0);

		p = str;
		while (*p) {
			mul_int(*this, 10);
			u_basic_int d = *(p) - '0';
			add_int(*this, d);
			++p;
		}
	}
};

int main(int argc, char **argv)
{
	std::cout << "sizeof char " << sizeof(unsigned char) << std::endl;
	std::cout << "sizeof short " << sizeof(unsigned short) << std::endl;
	std::cout << "sizeof int " << sizeof(unsigned int) << std::endl;
	std::cout << "sizeof long " << sizeof(unsigned long) << std::endl;
}
