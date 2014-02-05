#include <stack>
#include <iostream>
#include <iomanip>

#include "rng.h"

using namespace std;
using namespace wts;

template<typename T> class BST;
template<typename T> class BST_iterator;

template<typename T>
class BST_node {
public:
	BST_node(const T& x) : v(x), lc(0), rc(0) {}
	BST_node *insert(const T& x);
	T& val() { return v; }
private:
	friend class BST<T>;
	friend class BST_iterator<T>;
	T v;
	BST_node *lc;
	BST_node *rc;
};

template<typename T>
class BST {
public:
	BST() : root(0) {}
	BST_node<T> *insert(const T& x);
	typedef BST_iterator<T> iterator;
	iterator begin();
	iterator end();
	void intrv();
private:
	BST_node<T> *root;
	void _intrv(BST_node<T> *p);
};

template<typename T>
BST_node<T> *BST_node<T>::insert(const T& x) {
	if (x < v) {
		if (lc)
			return lc->insert(x);
		lc = new BST_node(x);
		return lc;
	}
	else if (x > v) {
		if (rc)
			return rc->insert(x);
		rc = new BST_node(x);
		return rc;
	}
	return this;
}

template<typename T>
BST_node<T> *BST<T>::insert(const T& x) {
	if (root)
		return root->insert(x);
	root = new BST_node<T>(x);
	return root;
}

template<typename T>
void BST<T>::_intrv(BST_node<T> *p) {
	if (p) {
		_intrv(p->lc);
		cout << setw(4) << p->val();
		_intrv(p->rc);
	}
}

template<typename T>
void BST<T>::intrv() {
	_intrv(root);
}

template<typename T>
class BST_iterator {
public:
	BST_iterator() : n(0), st() {}
	BST_iterator& operator++();
	bool operator!=(const BST_iterator& iter) { return (n != iter.n); }
	BST_node<T> *operator->() { return n; }
private:
	friend class BST<T>;
	BST_node<T> *n;
	std::stack<BST_node<T>*> st;
};

template<typename T>
typename BST<T>::iterator BST<T>::begin() {
	BST<T>::iterator iter;
	if (root) {
		iter.n = root;
		while (iter.n->lc) {
			iter.st.push(iter.n);
			iter.n = iter.n->lc;
		}
	}
	return iter;
}

template<typename T>
typename BST<T>::iterator BST<T>::end() {
	return BST<T>::iterator();
}

template<typename T>
BST_iterator<T> &BST_iterator<T>::operator++() {
	if (n) {
		if (n->rc) {
			st.push(n);
			n = n->rc;
			while (n->lc) {
				st.push(n);
				n = n->lc;
			}
		}
		else {
			bool yield = false;
			while (!st.empty() && !yield) {
				BST_node<T> *p = st.top();
				st.pop();
				yield = (p->lc == n);
				n = p;
			}
			if (!yield)
				n = 0;
		}
	}
	return *this;
}

int main()
{
	// Test1
	{
		BST<double> bst;
		bst.insert(5);
		bst.insert(2);
		bst.insert(1);
		bst.insert(3);
		bst.insert(8);
		bst.insert(7);
		bst.insert(9);
		bst.insert(6);
		bst.insert(4);
		bst.insert(2.5);

		bst.intrv();

		cout << "\n";

		for (BST<double>::iterator iter = bst.begin();
				iter != bst.end(); ++iter) {
			cout << setw(4) << iter->val();
		}

		cout << endl;
	}

	// Test2
	{
		BST<int> bst;
		SimpleRNG<int> rng(1, 100);
		for (size_t i = 0; i < 20; ++i) {
			int r = rng();
			cout << setw(4) << r;
			bst.insert(r);
		}
		cout << "\n";

		bst.intrv();

		cout << "\n";

		for (BST<int>::iterator iter = bst.begin();
				iter != bst.end(); ++iter) {
			cout << setw(4) << iter->val();
		}
	
		cout << endl;
	}


        return 0;
}
