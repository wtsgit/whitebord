/*
http://oj.leetcode.com/problems/evaluate-reverse-polish-notation/
Wed Dec 18 19:35:42 EST 2013


Evaluate Reverse Polish Notation

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or
another expression.

Some examples:

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

*/
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class Solution {
public:
	int evalRPN(vector<string> &tokens) {
		vector<int> temp;
		for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
			if (strlen((*it).c_str()) > 1 || isdigit((*it)[0])) {
				temp.push_back(atoi((*it).c_str()));
			}
			else {
				int b = temp.back();
				temp.pop_back();
				int a = temp.back();
				temp.pop_back();
				int c = 0;
				switch ((*it)[0]) {
					case '+': c = a + b; break;
					case '-': c = a - b; break;
					case '*': c = a * b; break;
					case '/': c = a / b; break;
				}
				temp.push_back(c);
			}
		}
		return temp.back();
	}
};

int main()
{
	Solution sol;

	vector<string> rpn1;
	rpn1.push_back("2");
	rpn1.push_back("1");
	rpn1.push_back("+");
	rpn1.push_back("3");
	rpn1.push_back("*");
	cout << sol.evalRPN(rpn1) << endl;

	rpn1.clear();
	rpn1.push_back("4");
	rpn1.push_back("13");
	rpn1.push_back("5");
	rpn1.push_back("/");
	rpn1.push_back("+");
	cout << sol.evalRPN(rpn1) << endl;

	rpn1.clear();
	rpn1.push_back("0");
	rpn1.push_back("3");
	rpn1.push_back("/");
	cout << sol.evalRPN(rpn1) << endl;

	return 0;
}
