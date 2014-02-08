#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template<class I>
I first_ge(I b, I e, typename I::value_type x) {
	while (b < e) {
		I m = b + (e-b)/2;
		if (x <= *m)
			e = m;
		else
			b = m+1;
	}
	return b;
}

template<class I>
I first_gt(I b, I e, typename I::value_type x) {
	while (b < e) {
		I m = b + (e-b)/2;
		if (x >= *m)
			b = m+1;
		else
			e = m;
	}
	return b;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;

	vector<int> v{1, 2, 3, 4, 5, 5, 5, 5, 6, 7, 8, 9, 10, 20, 20, 20, 20, 20, 30, 40, 50, 60, 70, 80, 90};
	for (size_t i = 0; i < v.size(); ++i)
		cout << "v[" << i << "]" << v[i] << endl;
	cout << endl;

	auto i = first_ge(v.begin(), v.end(), atoi(argv[1]));
	cout << "v[" << i - v.begin() << "]=" << ((i != v.end()) ? *i : -1) << endl;

	i = first_gt(v.begin(), v.end(), atoi(argv[1]));
	cout << "v[" << i - v.begin() << "]=" << ((i != v.end()) ? *i : -1) << endl;

        return 0;
}
