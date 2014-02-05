/*

A probabilistic question
http://www.mitbbs.com/article_t/JobHunting/32597711.html
Tue Dec 17 21:17:11 EST 2013

Alice and Bob plays a game with a coin.

They toss the coin to generate a sequence until pattern HHT or HTT appears.

If HHT comes up, Alice wins. If HTT, Bob wins.

1. Who has a larger chance to win
2. What's the probabilities for each of them

*/
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
	queue<string> seq;
	seq.push(string(""));

	size_t old_n = 0;
	size_t alice = 0;
	size_t bob = 0;
	size_t limit = 30;
	size_t n_seq = 0;
	double accu_prob_end = 0.0;
	double accu_alice_win = 0.0;
	double accu_bob_win = 0.0;
	while (!seq.empty()) {
		string &toss = seq.front();
		size_t n = toss.size();
		if (old_n != n) {
			double prob_end = (alice+bob)/(double)n_seq;
			accu_alice_win += (1-accu_prob_end) * alice/(double)n_seq;
			accu_bob_win += (1-accu_prob_end) * bob/(double)n_seq;
			accu_prob_end += (1-accu_prob_end) * prob_end;

			cout << "#toss = " << old_n
			     << " #seq = " << n_seq
			     << " Alice " << alice
			     << " Bob " << bob;
			cout << " prob(end) = " << prob_end;
			cout << " accu prob(end) = " << accu_prob_end;
			cout << " accu alice = " << accu_alice_win;
			cout << " accu bob = " << accu_bob_win;

			cout << endl;
			alice = 0;
			bob = 0;
			if (n > limit)
				break;
			old_n = n;
			n_seq = 0;
		}
		++n_seq;

		if (n >= 3 && toss[n-3] == 'H' && toss[n-2] == 'H' && toss[n-1] == 'T') {
			++alice;
			//cout << toss << " A" << endl;
		}
		else if (n >= 3 && toss[n-3] == 'H' && toss[n-2] == 'T' && toss[n-1] == 'T') {
			//cout << toss << " B" << endl;
			++bob;
		}
		else {
			//cout << toss << endl;
			seq.push(toss + 'H');
			seq.push(toss + 'T');
		}

		seq.pop();
	}
	return 0;
}
