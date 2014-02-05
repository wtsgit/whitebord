//
// CLRS 15.4 Longest common subsequence
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class LCS {
private:
	string X;
	string Y;
	vector<vector<int> > c;
	vector<vector<char> > b;
	size_t m;
	size_t n;
public:
	LCS(const string &x, const string &y) {
		reset(x, y);
	}

	void reset(const string &x, const string &y) {
		X = x;
		Y = y;
		m = X.size();
		n = Y.size();
		c.clear();
		b.clear();
		for (size_t i = 0; i <= m; ++i) {
			c.push_back(vector<int>(n+1));
			b.push_back(vector<char>(n+1));
		}
	}

	void solve() {
		for (size_t i = 0; i <= m; ++i) {
			c[i][0] = 0;
		}
		for (size_t j = 0; j <= n; ++j) {
			c[0][j] = 0;
		}
		for (size_t i = 1; i<= m; ++i) {
			for (size_t j = 1; j <= n; ++j) {
				if (X[i-1] == Y[j-1]) {
					c[i][j] = c[i-1][j-1] + 1;
					b[i][j] = 'V';
				}
				else if (c[i-1][j] >= c[i][j-1]) {
					c[i][j] = c[i-1][j];
					b[i][j] = '|';
				}
				else {
					c[i][j] = c[i][j-1];
					b[i][j] = '-';
				}
			}
		}
	}

	void print(ostream &os, size_t i, size_t j) {
		if (i == 0 || j == 0) {
			return;
		}
		if (b[i][j] == 'V') {
			print(os, i-1, j-1);
			os << X[i-1];
		}
		else if (b[i][j] == '|') {
			print(os, i-1, j);
		}
		else {
			print(os, i, j-1);
		}
	}

	void print(ostream &os) {
		print(os, X.size(), Y.size());
	}

	void print() {
		print(cout, X.size(), Y.size());
	}
};

class BrutalForce {
public:
	template<class CB> static
	void enumerate_substring(CB &cb,
				 string prefix,
				 string::const_iterator s,
				 string::const_iterator e) {
		if (s == e) {
			cb(prefix);
			return;
		}
		enumerate_substring(cb, prefix, s+1, e);
		prefix += *s;
		enumerate_substring(cb, prefix, s+1, e);
	}

	template<class CB> static
	void enumerate_substring(CB &cb,
				 string::const_iterator s,
				 string::const_iterator e) {
		enumerate_substring(cb, "", s, e);
	}

	static bool is_substring(const string &s, const string &sub) {
		size_t i = 0;
		for (size_t j = 0; j < sub.size(); ++j) {
			while (i < s.size() && s[i] != sub[j])
				++i;
			if (i >= s.size()) {
				return false;
			}
			++i;
		}
		return true;
	}

private:
	class CallBack {
	private:
		string s;
		string sub;
	public:
		CallBack(const string &s_) : s(s_) {}
		void operator()(const string &sub_) {
			if (is_substring(s, sub_) && sub_.size() > sub.size())
				sub = sub_;
		}
		string get() { return sub; }
	};

	string X;
	string Y;
	CallBack cb;

public:
	BrutalForce(const string &x, const string &y): X(x), Y(y), cb(y) {}
	void solve() {
		enumerate_substring(cb, X.begin(), X.end());
	}
	void print(ostream &os) {
		os << cb.get();
	}
	void print() {
		print(cout);
	}
};

int main()
{
	ostringstream os;
	string s1;
	string s2;

	s1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
	s2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
	LCS lcs(s1, s2);
	lcs.solve();
	lcs.print();
	cout << endl;

	s1 = "ACCGGTCGAGTGCGCGGAA";
	s2 = "GTCGTTCGGAATGCCGTTGC";
	lcs.reset(s1, s2);
	lcs.solve();
	lcs.print(os);
	if (BrutalForce::is_substring(s1, os.str()) && BrutalForce::is_substring(s2, os.str())) {
		os << ": verified";
	}
	cout << "dp=> " << os.str() << endl;

	os.str("");
	BrutalForce bf(s1, s2);
	bf.solve();
	bf.print(os);
	if (BrutalForce::is_substring(s1, os.str()) && BrutalForce::is_substring(s2, os.str())) {
		os << ": verified";
	}
	cout << "bf=> " << os.str() << endl;

        return 0;
}
