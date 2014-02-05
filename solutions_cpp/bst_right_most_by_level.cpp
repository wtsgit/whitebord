#include <fstream>
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include <cassert>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

template<typename T>
class BstNode {
public:
	BstNode(const T &t) : l(0), r(0), v(t) {}
	const T& val() const { return v; }
	const BstNode* insert(const T& t) {
		if (t < v)
			return l ? l->insert(t) : l = new BstNode(t);
		else if (t > v)
			return r ? r->insert(t) : r = new BstNode(t);
		return 0;
	}
	template<typename F>
	void visit_right_most(F f) const {
		int maxlvl = -1;
		stack<pair<int, const BstNode *> > s;
		s.push(make_pair(-1, this));
		while (!s.empty()) {
			int lvl = s.top().first;
			const BstNode *p = s.top().second;
			s.pop();
			while (p) {
				if (++lvl > maxlvl) {
					f(p->v);
					maxlvl = lvl;
				}
				if (p->l && p->r)
					s.push(make_pair(lvl, p->l));
				p = p->r ? p->r : p->l;
			}
		}
	}
	template<typename F>
	void visit_right_most_bfs(F f) const {
		queue<const BstNode *> q;
		const BstNode *p = 0;
		q.push(this);
		while (!q.empty()) {
			const BstNode *rm = q.back();
			f(rm->v);
			do {
				p = q.front();
				q.pop();
				if (p->l)
					q.push(p->l);
				if (p->r)
					q.push(p->r);
			} while (p != rm);
		}
	}
	template<typename F>
	void post_order_trav_recur(F f) const {
		if (l)
			l->post_order_trav_recur(f);
		if (r)
			r->post_order_trav_recur(f);
		f(v);

	}
	template<typename F>
	void post_order_trav(F f) const {
		const BstNode *pprev = this;
		stack<const BstNode *> s;
		s.push(this);
		while (!s.empty()) {
			const BstNode *p = s.top();
			for (;;) {
				const BstNode *pnext = 0;
				if (pprev == p->l)
					pnext = p->r;
				else if (pprev != p->r)
					pnext = p->l ? p->l : p->r;
				pprev = p;
				if (!pnext)
					break;
				p = pnext;
				s.push(p);
			}
			f(p->v);
			s.pop();
		}
	}
private:
	BstNode *l;
	BstNode *r;
	T v;
};

int main()
{
	ifstream urandom("/dev/urandom", ios::in|ios::binary);
	unsigned int seed;
	urandom.read((char *)&seed, sizeof(seed));
	srandom(seed);

	{
		BstNode<int> node(random() % 100);
		int cnt = 1;
		for (int i = 0; i < 10000 && cnt < 20; ++i) {
			if (node.insert(random() % 100))
				cnt++;
		}

		node.post_order_trav_recur([] (int v) { cout << setw(4) << v; } );
		cout << endl;

		node.post_order_trav([] (int v) { cout << setw(4) << v; } );
		cout << endl;
	}

	{
		BstNode<int> node(2);
		node.post_order_trav_recur([] (int v) { cout << setw(4) << v; } );
		cout << endl;

		node.post_order_trav([] (int v) { cout << setw(4) << v; } );
		cout << endl;
	}

	{
		BstNode<int> node(2);
		node.insert(1);
		node.post_order_trav_recur([] (int v) { cout << setw(4) << v; } );
		cout << endl;

		node.post_order_trav([] (int v) { cout << setw(4) << v; } );
		cout << endl;
	}

	{
		BstNode<int> node(2);
		node.insert(3);
		node.post_order_trav_recur([] (int v) { cout << setw(4) << v; } );
		cout << endl;

		node.post_order_trav([] (int v) { cout << setw(4) << v; } );
		cout << endl;
	}

	return 0;
}


#if 0 
	node->visit_right_most_bfs([] (int v) { cout << setw(4) << v; } );
	cout << endl;

	node->visit_right_most([] (int v) { cout << setw(4) << v; } );
	cout << endl;
#endif
