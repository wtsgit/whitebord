/*
http://oj.leetcode.com/problems/valid-palindrome/
Fri Jan 10 23:10:53 UTC 2014


Valid Palindrome

Given a string, determine if it is a palindrome, considering only
alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good
question to ask during an interview.

For the purpose of this problem, we define empty string as valid
palindrome.
*/

#include <iostream>
#include <string>

using namespace std;

/*
string is [start, end),
1. true if start == end;
2. move forward start until first isalnum, move backward end until first isalnum.
3. false if *start != *end;
4. true
*/
class Solution {
public:
	bool isPalindrome(string s) {
		size_t i = 0;
		size_t j = s.size();
		while (true) {
			while (i != j && !isalnum(s[j-1]))
				--j;
			while (i != j && !isalnum(s[i]))
				++i;
			if (i == j)
				break;
			if (tolower(s[i]) != tolower(s[j-1]))
				return false;
			s[i] = '$';
			s[j-1] = '$';

		}
		return true;
	}
};

int main()
{
	Solution s;
	cout << s.isPalindrome("A man, a plan, a canal: Panama") << endl;
	cout << s.isPalindrome("Panama") << endl;
	return 0;
}
