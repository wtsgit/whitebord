#ifndef __WTS_RNG__
#define __WTS_RNG__

#include <cstdlib>
#include <sys/time.h>
#include <fstream>
#include <stdexcept>
#include <limits>

namespace wts {

template<typename T> class SimpleRNG
{
public:
	enum IntervalType { Default, Inclusive, HalfOpen };
	SimpleRNG(T l, T h, IntervalType itype = Default);
	T operator()();
	static void init();
	static void init_by_time();
private:
	T lo;
	T hi;
	int adj;
};

template<typename T>
SimpleRNG<T>::SimpleRNG(T l, T h, IntervalType itype)
{
	if (l >= h)
		throw std::domain_error("Bad interval");

	lo = l;
	hi = h;
	adj = 0;

	if (std::numeric_limits<T>::is_integer) {
		adj = 1;
		if (itype == Default || itype == Inclusive) {
			if (hi == std::numeric_limits<T>::max())
				throw std::domain_error("Bad interval");
			hi += 1;
		}
	}
	else if (itype == Default || itype == HalfOpen) {
		adj = 1;
	}

	init();
}

template<typename T>
void SimpleRNG<T>::init_by_time()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	srandom(tv.tv_sec);
}

template<typename T>
void SimpleRNG<T>::init()
{
	std::ifstream urandom("/dev/urandom", std::ios::in|std::ios::binary);
	unsigned int seed;
	urandom.read((char *)&seed, sizeof(seed));
	srandom(seed);
}

template<typename T>
T SimpleRNG<T>::operator()()
{
	double rd = random()/((double)RAND_MAX + adj);
	return (T)(rd * (hi - lo) + lo);
}

} // namespace wts

#endif
