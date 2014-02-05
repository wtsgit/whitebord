/*
http://www.mitbbs.com/article_t/JobHunting/32602853.html
Mon Jan 13 16:02:24 EST 2014

G:
一个队列，每个元素自身有一个数值，并且有一个计数，存储着排在这个元素前面有几
个比他的数值大的元素，比如[(3,2),(2,2),(4,1),(6,0)], 如果现在这个队列突然被
随机打乱作为输入，比如[(2,2),(6,0),(4,1),(3,2)],请据此恢复输出原来队列。
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> IntPair;
typedef vector<IntPair> IntPairVec;

template <class T> class PairGreater {
public:
	bool operator()(const pair<T, T> &a, const pair<T, T> &b) const {
		return a.first > b.first;
	}
};

template <class T> class PairLess {
public:
	bool operator()(const pair<T, T> &a, const pair<T, T> &b) const {
		return a.first < b.first;
	}
};

ostream& operator<<(ostream &os, const IntPair &p) {
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

ostream& operator<<(ostream &os, const IntPairVec &vec) {
	for (IntPairVec::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		os << *it << " ";
	}
	return os;
}

/*
Thought1: The pair for the largest number max must be (max, 0) since
there are 0 number larger than it. The 2nd largest number max2nd
might be (max2nd, 1) or (max2nd, 0) depending on its relative
position to max. The 3rd largest number max3rd might be (max3rd,
1), (max3rd, 2) or (max3rd, 0), etc.

Each pair is (num, rank).  We sort the list according to num and
start with the largest. The rank decides the insertion position of
of the pair in the restored list.

This is a O(nlogn) + O(n^2) algorithm.
*/
IntPairVec restore_pairs(IntPairVec vec) {
	sort(vec.begin(), vec.end(), PairGreater<int>());
	IntPairVec result;
	for (IntPairVec::const_iterator cit=vec.begin(); cit != vec.end(); ++cit) {
		if (cit->second > result.size())
			throw std::invalid_argument("Bad input");
		result.insert(result.begin() + cit->second, *cit);
	}
	return result;

}

/*
Thought2. Assume we have reserved space for the restored list.
Consider the smallest number (num, rank). The rank is its
index in the restored list. Now we relabel the restored list and 
and skip the occupied cells, The rank of the next pair is the
index in the relabeled list.
*/
IntPairVec restore_pairs_again(IntPairVec vec) {
	sort(vec.begin(), vec.end(), PairLess<int>());
	IntPairVec result(vec.size());
	vector<bool> occupied(vec.size(), false);
	for (IntPairVec::const_iterator cit=vec.begin(); cit != vec.end(); ++cit) {
		IntPairVec::iterator iit = result.begin();
		size_t i = 0;
		vector<bool>::iterator bit = occupied.begin();
		while (true) {
			while (bit != occupied.end() && *bit == true) {
				++bit;
				++iit;
			}
			if (i == cit->second || iit == result.end())
				break;
			++i;
			++bit;
			++iit;
		}
		if (iit == result.end())
			throw invalid_argument("Bad input");
		*iit = *cit;
		*bit = true;
	}
	return result;
}


int main()
{
	IntPairVec vec = {{2,2},{6,0},{4,1},{3,2}};
	cout << vec << endl;
	cout << restore_pairs(vec) << endl;
	cout << endl;

	vec = {{2,0},{1,1},{4,0},{3,1}};
	cout << vec << endl;
	cout << restore_pairs(vec) << endl;
	cout << endl;

	vec = {{2,2},{6,0},{4,1},{3,2}};
	cout << vec << endl;
	cout << restore_pairs_again(vec) << endl;
	cout << endl;

	vec = {{2,0},{1,1},{4,0},{3,1}};
	cout << vec << endl;
	cout << restore_pairs_again(vec) << endl;
	cout << endl;

        return 0;
}
