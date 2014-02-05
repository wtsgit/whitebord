// http://www.mitbbs.com/article_t/JobHunting/32162879.html
//
// A(1)... A(N), B(1)... B(N), C(1)... C(n), minimize the sum,
// There are N variables in sum, and A(n) or B(n) could not exist together. And
// C(n) is counted when there is a switch from A to B or B to A. Calculate the
// minimal sum by DP.
// Example: A(1)=3, A(2)=4, A(3)=5; B(1)=1, B(2)=2, B(3)=5, C(1)=1, C(2)=2, C(3)=3.
// Output: A(1)+B(2)+C(2)+B(3) (not the true result). There is C(2) since from 
// status 1 to 2, there is a switch from A to B.
//

#include <iostream>
#include <vector>
#include <limits>
#include <cassert>
#include <bitset>

using namespace std;

class MinSumBrutal {
private:
	const size_t n;
	const vector<int> &A;
	const vector<int> &B;
	const vector<int> &C;
public:
	MinSumBrutal(const vector<int> &A_,
		const vector<int> &B_,
		const vector<int> &C_)
	: n(A_.size()), A(A_), B(B_), C(C_)
	{
		assert(n > 0);
		assert(n <= (sizeof(int)*8));
		assert(n == B_.size());
		assert(n == C_.size());
	}
	friend class CheckMin;
private:
	class CheckMin {
	private:
		const MinSumBrutal *data;
		const size_t n;
		unsigned int cand_vec;
		long cand_sum;
	public:
		CheckMin(MinSumBrutal *data_)
		: data(data_), n(data_->n), cand_sum(numeric_limits<long>::max())
		{}
		void operator()(unsigned int vec) {
			bitset<sizeof(int)*8> bs(vec);
			long sum = 0;
			for (size_t i = 0; i < n; ++i) {
				sum += (bs[i] == 0) ? data->A[i] : data->B[i];
				sum += ((i > 0) && (bs[i] != bs[i-1])) ? data->C[i] : 0;
			}
			if (sum < cand_sum) {
				cand_sum = sum;
				cand_vec = vec;
			}
		}
		long get_sum() { return cand_sum; }
		unsigned int get_vec() { return cand_vec; }
	};
	template <class F>
	void iterate(F &f) {
		unsigned int mask = 0;
		for (size_t i = 0; i < n; ++i) {
			mask <<= 1;
			mask |= 1;
		}
		unsigned int vec = 0;
		do {
			f(vec);
			++vec;
		} while ((vec & mask) != mask);
	}
public:
	void solve() {
		CheckMin ckmin(this);
		iterate(ckmin);
		bitset<sizeof(int)*8> bs(ckmin.get_vec());
		cout << "Min sum is: " << ckmin.get_sum() << endl;
		cout << "Solution: "; 
		for (size_t i = 0; i < n; ++i) {
			cout << (bs[i] ? "B" : "A");
			cout << i;
		}
		cout << endl;
	}
};

class MinSumDP {
private:
	const size_t n;
	const vector<int> &A;
	const vector<int> &B;
	const vector<int> &C;
public:
	MinSumDP(const vector<int> &A_,
		const vector<int> &B_,
		const vector<int> &C_)
	: n(A_.size()), A(A_), B(B_), C(C_)
	{
		assert(n > 0);
		assert(n <= (sizeof(int)*8));
		assert(n == B_.size());
		assert(n == C_.size());
	}
	void solve() {
		vector<int> min_pref_A(n);
		vector<int> min_pref_B(n);
		min_pref_A[0] = A[0];
		min_pref_B[0] = B[0];
		for (size_t i = 1; i < n; ++i) {
			int sum_jump = min_pref_B[i-1] + C[i] + A[i];
			int sum_nojump = min_pref_A[i-1] + A[i];
			if (sum_jump < sum_nojump) {
				min_pref_A[i] = sum_jump;
			}
			else {
				min_pref_A[i] = sum_nojump;
			}

			sum_jump = min_pref_A[i-1] + C[i] + B[i];
			sum_nojump = min_pref_B[i-1] + B[i];
			if (sum_jump < sum_nojump) {
				min_pref_B[i] = sum_jump;
			}
			else {
				min_pref_B[i] = sum_nojump;
			}
		}
		cout << "Min sum is " <<  min(min_pref_B[n-1], min_pref_A[n-1])
		<< endl;
	}

};

int main()
{
	vector<int> A;
	A.push_back(1);
	A.push_back(3);
	A.push_back(1);
	A.push_back(1);
	A.push_back(10);
	vector<int> B;
	B.push_back(1);
	B.push_back(2);
	B.push_back(10);
	B.push_back(-23);
	B.push_back(1);
	vector<int> C;
	C.push_back(1);
	C.push_back(2);
	C.push_back(3);
	C.push_back(4);
	C.push_back(5);

	MinSumBrutal msb(A, B, C);
	msb.solve();

	MinSumDP dp(A, B, C);
	dp.solve();

        return 0;
}
