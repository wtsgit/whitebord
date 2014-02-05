/*
http://www.mitbbs.com/article_t/JobHunting/32606279.html
Mon Jan 13 23:21:16 EST 2014

发信人: starapi (STAR test API), 信区: JobHunting
标  题: 这个G题是DFS还是DP
发信站: BBS 未名空间站 (Thu Jan  9 13:03:06 2014, 美东)

Given a byte array, which is an encoding of characters. Here is the rule:

a. If the first bit of a byte is 0, that byte stands for a one-byte 
character

b. If the first bit of a byte is 1, that byte and its following byte 
together stand for a two-byte character 
Now implement a function to decide if the last character is a one-byte 
character or a two-byte character
Constraint: You must scan the byte array from the end to the start. 
Otherwise it will be very trivial.
*/
#include <iostream>
#include <vector>

using namespace std;

bool isTwoByte(const vector<char> &ba) {
	if (ba.size() <= 1)
		return false;
	char flag = 0;
	for (vector<char>::const_reverse_iterator crit = ba.rbegin()+1;
			crit != ba.rend() && ((*crit & '\x80') != '\x00'); ++crit) {
		flag ^= *crit;
	}
	return ((flag & '\x80') != '\x00');
}


int main()
{
	vector<char> v = {'\x80','\x00', '\x80', '\x80'};
	cout << isTwoByte(v) << endl;

	v = {'\x80','\x80', '\x80', '\x00'};
	cout << isTwoByte(v) << endl;

	v = {'\x80','\x00', '\x80', '\x00'};
	cout << isTwoByte(v) << endl;

	return 0;
}
