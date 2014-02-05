/*
http://www.mitbbs.com/article_t1/JobHunting/32582249_0_1.html
Tue Jan 14 01:44:04 EST 2014

第二轮是给一个int N，让输出所有的长度为N的valid string的个数，valid string的
定义是由A,B,C三种字母组成，并且在这个string中任意连续的三个字母不能包括A,B,C
三个字母，比如BACCA就不是valid string，因为前三个字母B,A,C包含了这三个字母。
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>

using namespace std;

void generateABCStrings(vector<string> &svec, string str, const size_t start, const size_t n) {
	if (start == n) {
		svec.push_back(str);
	}
	else {
		generateABCStrings(svec, str+'A', start+1, n);
		generateABCStrings(svec, str+'B', start+1, n);
		generateABCStrings(svec, str+'C', start+1, n);
	}
}

bool isValidString(const string &str) {
	vector<string> invalid_patterns{"ABC", "ACB", "BAC", "BCA", "CAB", "CBA"};
	for (vector<string>::const_iterator cit = invalid_patterns.begin(); cit != invalid_patterns.end(); ++cit) {
		if (str.find(*cit) != string::npos)
			return false;
	}
	return true;
}

size_t countValidString(const size_t n) {
	if (n == 0)
		return 1; 
	if (n == 1)
		return 3;
	size_t a = 3; // Ending AA BB CC
	size_t b = 6; // Ending AB AC BA BC CA CB

	for (size_t i = 3; i <= n; ++i) {
		size_t new_a = a + b;
		size_t new_b = 2 * a + b;
		a = new_a;
		b = new_b;
	}
	
	return a + b;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	const size_t n = atoi(argv[1]);
	vector<string> svec;
	generateABCStrings(svec, "", 0, n);
	//copy(svec.begin(), svec.end(), ostream_iterator<string>(cout, "\n"));
	size_t n_valid = 0;
	for (vector<string>::const_iterator cit = svec.begin(); cit != svec.end(); ++cit) {
		 // cout << *cit << " " << isValidString(*cit) << endl;
		 if (isValidString(*cit))
			 ++n_valid;
	}
	cout << n_valid << endl;
	cout << countValidString(n) << endl;

        return 0;
}
