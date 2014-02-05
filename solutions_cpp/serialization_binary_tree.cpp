#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <cassert>

template<typename T> class BinaryTree;

template<typename T>
class BinaryTreeNode {
public:
	BinaryTreeNode() {}
	BinaryTreeNode(const T &v) : val(v) {}
	~BinaryTreeNode() { delete lc; delete rc; }

private:
	T val{};
	BinaryTreeNode *lc{};
	BinaryTreeNode *rc{};

friend class BinaryTree<T>;
};

template<typename T>
class BinaryTree {
public:
	BinaryTree() {}
	explicit BinaryTree(std::istream &is) {
		is >> *this;
	}

	template<class I>
	BinaryTree(I b, I e) {
		construct(root, b, e);
	}

	friend std::istream & operator >> (std::istream &is, BinaryTree<T> &bt) {
		bt.clear();
		std::istream_iterator<std::string> isit(is);
		std::istream_iterator<std::string> isit_end;
		bt.construct(bt.root, isit, isit_end);
		return is;
	}

	friend std::ostream & operator << (std::ostream &os, const BinaryTree<T> &bt) {
		std::ostream_iterator<std::string> osit(os, " ");
		bt.serialize(bt.root, osit);
		return os;
	}

	~BinaryTree() { clear(); }

	void clear() { delete root; root = nullptr; }

private:
	template<class I>
	I construct(BinaryTreeNode<T> *&n, I b, I e) {
		n = nullptr;
		if ((b != e) && (*b != "#")) {
			T v;
			std::stringstream(*b++) >> v;
			n = new BinaryTreeNode<T>(v);
			return construct(n->rc, construct(n->lc, b, e), e);
		}
		return ++b;
	}

	template<class I>
	I serialize(const BinaryTreeNode<T> *p, I it) const {
		if (p) {
			std::ostringstream oss;
			oss << p->val;
			*it++ = oss.str();
			return serialize(p->rc, serialize(p->lc, it));
		}
		*it++ = "#";
		return it;
	}

private:
	BinaryTreeNode<T> *root{};
};

int main()
{
	std::stringstream iss("30 10 50 # # # 20 45 # # 35 # #");
	BinaryTree<int> bt(iss);
	std::cout << bt << std::endl;

        return 0;
}
