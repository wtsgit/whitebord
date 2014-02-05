#include <iostream>
#include <cstdlib>
#include <cmath>

typedef double (*monotone_incr_fun)(const double);

double reverse_fun_bsearch(
		monotone_incr_fun f,
		double x,
		double r0,
		double r1,
		double e = 1e-6)
{
	double r, d;

	for (;;) {
		r = (r0 + r1) / 2;
		if (r1 - r0 < r * e)
			break;
		d = f(r) - x;
		if (d > 0)
			r1 = r;
		else if (d < 0)
			r0 = r;
		else
			break;
	}

	return r;
}

double sqr(double x)
{
	return x * x;
}

double sqrt_bsearch(double x)
{
	if (x < 0 || x == 1.0)
		return x;

	if (x > 1) {
		return reverse_fun_bsearch(sqr, x, 1.0, x);
	}

	if (x < 1) {
		return reverse_fun_bsearch(sqr, x, x, 1.0);
	}

	return x;
}

double sqr_bsearch(double x)
{
	return reverse_fun_bsearch(std::sqrt, x, 0.0, x*x*2);
}

int main(int argc, char **argv)
{
	double x = 0.0;
	if (argc > 1) {
		x = atof(argv[1]);
		std::cout << x << std::endl;
		std::cout << sqrt_bsearch(x) << std::endl;
		std::cout << std::sqrt(x) << std::endl;

		std::cout << std::endl;
		std::cout << sqr_bsearch(x) << std::endl;
		std::cout << x * x << std::endl;
	}

	return 0;
}
