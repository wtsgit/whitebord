#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template<class T>
class Node;

template<class T>
class Bound_Space_Traversal;

template<class T>
class Visitor {
public:
	//void operator ()(Node<T> *c) { std::cout << c->data << std::endl; }
	void operator ()(const T &d) { std::cout << d << std::endl; }
};

template<class T>
void cout_data(const T &d)
{
	std::cout << d << std::endl; 
}

template<class T>
class Node {
private:
	T data;
	unsigned int flag;
	Node *l;
	Node *r;
	static void go_up(Node *&c, Node *&p);
	friend class Bound_Space_Traversal<T>;
	bool is_leaf() { return ((l == 0) && (r == 0)); }
public:
	Node() : data(), flag(), l(), r() {}
	Node(const T& d) : data(d), flag(), l(), r() {}
	Node& insert(const T&);
	template<class F> void recursive_in_order_walk(F);
	template<class F> void two_bit_overhead_in_order_walk(F f);
};

template <class T>
Node<T>& Node<T>::insert(const T& incoming)
{
	if (incoming < data) {
		if (l != 0) {
			return l->insert(incoming);
		}
		l = new Node(incoming);
		return *l;
	}

	if (data < incoming) {
		if (r != 0) {
			return r->insert(incoming);
		}
		r = new Node(incoming);
		return *r;
	}

	return *this;
}

template<class T>
template<class F>
void Node<T>::recursive_in_order_walk(F f)
{
	if (l != 0) {
		l->recursive_in_order_walk(f);
	}

	f(data);

	if (r != 0) {
		r->recursive_in_order_walk(f);
	}
}

template<class T>
void Node<T>::go_up(Node *&c, Node *&p)
{
	assert(c);
	if (p == 0) {
		c = 0;
		return;
	}

	if (p->flag == 0x10) {
		/* c is left child of p */
		Node *t = p->l; p->l = c; c = p; p = t;
	}
	else if (p->flag == 0x01) {
		/* c is right child of p */
		Node *t = p->r; p->r = c; c = p; p = t;
	}
	else {
		assert(0);
	}
}

template<class T>
template<class F>
void Node<T>::two_bit_overhead_in_order_walk(F f)
{
	Node *c = this;
	Node *p = 0;

	while (c) {
		cout << "\t\tArriving at \"" << c->data << "\"";
		cout << " (flag=" << hex << setw(2) << setfill('0') << c->flag << ")" << endl;
		if (c->flag == 0) {
			c->flag = 0x10;
			if (c->l) {
				if (c->l->is_leaf()) {
					cout << "\t\tVisiting left child " << c->l->data << endl;
					f(c->l->data);
				}
				else {
					cout << "\t\tGoing to left subtree \"" << c->l->data << "\"" << endl;
					Node *t = c->l; c->l = p; p = c; c = t;
				}
			}
		}
		else if (c->flag == 0x10) {
			cout << "\t\tVisiting node \"" << c->data << "\"" << endl;
			f(c->data);
			c->flag = 0x01;
			if (c->r) {
				if (c->r->is_leaf()) {
					cout << "\t\tVisiting right child \"" << c->r->data << "\"" << endl;
					f(c->r->data);
				}
				else {
					cout << "\t\tGoing to right subtree \"" << c->r->data << "\"" << endl;
					Node *t = c->r; c->r = p; p = c; c = t;
				}
			}
		}
		else if (c->flag == 0x01) {
			c->flag = 0;
			cout << "\t\tGoing up to \"" << (p ? (string)p->data : (string)"nil") << "\"" << endl;
			go_up(c, p);
		}
		else {
			assert(0);
		}
	}
}

template<class T>
class Bound_Space_Traversal {
private:
	Node<T> *c;
	Node<T> *p;
	Node<T> *sentinel;
public:
	static void swap_ptr(Node<T> *c)
	{
		assert(c);
		Node<T> *t = c->l; c->l = c->r; c->r = t;
	}
	static void sort_ptr(Node<T> *c)
	{
		assert(c);
		assert(c->l && c->r);
		if (c->l > c->r) {
			Node<T> tmp = *(c->r); *(c->r) = *(c->l); *(c->l) = tmp;
			swap_ptr(c);
		}
	}
	void go_up()
	{
		Node<T> *t;
		assert(c);
		assert(p);
		if (p == sentinel) { c = sentinel; p = 0; return; }
		assert(p->l || p->r);
		if (p->l == 0) { t = c; c = p; p = p->r; c->r = t; }
		else { t = c; c = p; p = p->l; c->l = t; }
	}
	void go_left()
	{
		assert(c);
		assert(c->l);
		Node<T> *t = c->l; c->l = p; p = c; c = t;
	}
	void go_right()
	{
		assert(c);
		assert(c->r);
		Node<T> *t = c->r; c->r = p; p = c; c = t;
	}
	void trav(Node<T> *root, Visitor<T> visit)
	{
		bool going_down = true;
		c = root; sentinel = new Node<T>; p = sentinel; 
		while (c != sentinel) {
			if (going_down) {
				if (c->l == 0) {
					visit(c->data);
					if (c->r == 0) { go_up(); going_down = false; }
					else { go_right(); }
				}
				else if (c->r == 0) { go_left(); }
				else {
					sort_ptr(c);
					go_left();
				}
			}
			// going up
			else if (c->r == 0) { visit(c->data); go_up(); }
			else if (c->l == 0) { go_up(); }
			else if (c->l < c->r) { // visited left subtree
				visit(c->data);
				// now visit right subtree
				going_down = true;
				swap_ptr(c); go_left();
			}
			else { swap_ptr(c); go_up(); }
		}
		delete sentinel;
	}
};

int main()
{
	Node<string> root("The");
	root.insert("keyword");
	root.insert("this");
	root.insert("identifies");
	root.insert("a");
	root.insert("special");
	root.insert("type");
	root.insert("of");
	root.insert("pointer");
	root.insert("Suppose");
	root.insert("that");
	root.insert("you");
	root.insert("create");
	root.insert("an");
	root.insert("object");
	root.insert("named");
	root.insert("x");
	root.insert("of");
	root.insert("class");
	root.insert("and");
	root.insert("class");
	root.insert("A");
	root.insert("has");
	root.insert("a");
	root.insert("nonstatic");
	root.insert("member");
	root.insert("function");
	root.insert("If");
	root.insert("you");
	root.insert("call");
	root.insert("the");
	root.insert("function");
	root.insert("the");
	root.insert("keyword");
	root.insert("this");
	root.insert("in");
	root.insert("the");
	root.insert("body");
	root.insert("of");
	root.insert("stores");
	root.insert("the");
	root.insert("address");
	root.insert("of");
	root.insert("x");
	root.insert("You");
	root.insert("cannot");
	root.insert("declare");
	root.insert("the");
	root.insert("this");
	root.insert("pointer");
	root.insert("or");
	root.insert("make");
	root.insert("assignments");
	root.insert("to");
	root.insert("it");

	root.recursive_in_order_walk(cout_data<string>);
	//root.two_bit_overhead_in_order_walk(cout_data<string>);
	Bound_Space_Traversal<string> string_tree_trav;
	string_tree_trav.trav(&root, Visitor<string>());

	Node<int> iroot(100);
	iroot.insert(-1);
	iroot.insert(5);
	iroot.insert(4);
	iroot.insert(3);
	iroot.insert(2);
	iroot.insert(1);
	iroot.insert(1);
	iroot.insert(0);
	iroot.insert(1000);
	iroot.insert(200);
	iroot.insert(500);
	iroot.insert(750);
	iroot.insert(300);

	iroot.recursive_in_order_walk(cout_data<int>);
	//iroot.two_bit_overhead_in_order_walk(cout_data<int>);
	Bound_Space_Traversal<int> int_tree_trav;
	int_tree_trav.trav(&iroot, Visitor<int>());

        return 0;
}
