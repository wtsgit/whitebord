/*
http://oj.leetcode.com/problems/simplify-path/
Mon Feb  3 12:09:35 EST 2014


Simplify Path

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

click to show corner cases.
Corner Cases:

    Did you consider the case where path = "/../"?
    In this case, you should return "/".

    Another corner case is the path might contain multiple slashes
    '/' together, such as "/home//foo/".
    In this case, you should ignore redundant slashes and return
    "/home/foo".
*/
#include <iostream>
#include <string>
#include <deque>
#include <cctype>

using namespace std;

class Solution {
public:
	string simplifyPath(string path) {
		string s;
		size_t start = 0;
		while (start < path.size() && isspace(path[start]))
			++start;
		if (start == path.size())
			return s;
		deque<string> buf;
		if (path[start] == '/')
			buf.push_back("/");
		while (start < path.size()) {
			while (start < path.size() && path[start] == '/')
				++start;
			size_t i = start;
			while (i < path.size() && path[i] != '/')
				++i;
			size_t len = i-start;
			if (len > 0 && path.substr(start, len) != ".") {
				if (buf.size() == 0 || buf.back() == ".." || path.substr(start, len) != "..") {
					buf.push_back(path.substr(start, len));
				}
				else if (buf.back() != "/") {
					buf.pop_back();
				}
			}
			start = i;
		}

		if (buf.size() == 0) {
			s = ".";
			return s;
		}
		if (buf.front() == "/") {
			s = buf.front();
			buf.pop_front();
		}
		if (buf.size() > 0) {
			s += buf.front();
			buf.pop_front();
		}
		for (auto x : buf)
			s += "/" + x;

		return s;
	}
};

int main(int argc, char **argv)
{
	if (argc < 2)
		return 1;
	Solution s;
	cout << s.simplifyPath(argv[1]) << endl;
        return 0;
}

