#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <random>

using namespace std;

void generateAll(vector<string> &vs, const string &s, const size_t n) {
	if (n == 0) {
		vs.push_back(s);
		return;
	}
	for (char c = '0'; c <= '9'; ++c) {
		string ns(s);
		ns.push_back(c);
		generateAll(vs, ns, n-1);
	}
}

class RandomDStringGenerator {
private:
	random_device rd;
	default_random_engine rng{rd()};
	uniform_int_distribution<char> u{'0','9'};
	const size_t n = 5;
public:
	RandomDStringGenerator(size_t n) : n(n) {}
	string operator()() {
		string s;
		size_t i = n;
		while (i-- > 0) {
			s.push_back(u(rng));
		}
		return s;
	}
};

void brutalSub(string &smallest, const string &prefix,
		const string &s, const size_t r) {

	if (prefix.size() == r) {
		if (prefix < smallest)
			smallest = prefix;
		return;
	}

	if (prefix.size() + s.size() == r) {
		if (prefix + s < smallest)
			smallest = prefix + s;
		return;
	}

	if (prefix.size() + s.size() < r) {
		return;
	}

	if (s.size() > 0) {
		brutalSub(smallest, prefix+s[0], s.substr(1, s.size()-1), r);
		brutalSub(smallest, prefix, s.substr(1, s.size()-1), r);
	}
}

// Correct algorithm but no proof yet.
// Could optimize by avoiding searching from beginning each time.
string bubble(string s, size_t k) {
	if (k >= s.size())
		return string();
	while (k > 0) {
		size_t i;
		for (i = 0; i <= s.size()-2; ++i) {
			if (s[i] > s[i+1])
				break;
		}
		s.erase(i,1);
		--k;
	}
	return s;
}


// Another way is to use selection: select min from proper range each time.
string insertion(string s, size_t k) {
}

int main(int argc, char **argv)
{
	if (argc < 4)
		return 0;

	stringstream ss(argv[1]);
	size_t n;
	ss >> n;

	ss.str(argv[2]);
	ss.seekg(0);
	size_t l;
	ss >> l;

	ss.str(argv[3]);
	ss.seekg(0);
	size_t k;
	ss >> k;

	/*
	vector<string> vs;
	generateAll(vs, "", n);
	copy(vs.begin(), vs.end(), ostream_iterator<string>(cout, "\n"));
	*/
	if (l <= k)
		return 0;
	RandomDStringGenerator rdsg(l);	
	for (size_t i = 0; i < n; ++i) {
		string s(rdsg());
		string smallest(l-k, '9');
		brutalSub(smallest, "", s, s.size()-k);
		string smallest_bubble = bubble(s, k);
		cout << s << ": " << smallest << (smallest == smallest_bubble ? "\033[32m=\033[39m" : "\033[31m!\033[39m") << bubble(s, k) << endl;
	}
        return 0;
}
