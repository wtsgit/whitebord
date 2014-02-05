/*
http://oj.leetcode.com/problems/clone-graph/
Mon Jan  6 11:02:21 EST 2014


Clone Graph

Clone an undirected graph. Each node in the graph contains a label
and a list of its neighbors.

OJ's undirected graph serialization:

Nodes are labeled uniquely.
We use # as a separator for each node, and , as a separator for
node label and each neighbor of the node.

As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three
parts as separated by #.

    First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
    Second node is labeled as 1. Connect node 1 to node 2.
    Third node is labeled as 2. Connect node 2 to node 2 (itself),
    thus forming a self-cycle.

Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
	 / \
	 \_/
*/

#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * Definition for undirected graph.
 */
struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == 0)
			return 0;

		queue<pair<UndirectedGraphNode *, UndirectedGraphNode **> > q;
		unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> m;
		UndirectedGraphNode *new_node = 0;
		q.push(make_pair(node, &new_node));
		while (!q.empty()) {
			UndirectedGraphNode *p = q.front().first;
			UndirectedGraphNode **pp = q.front().second;
			q.pop();
			unordered_map<UndirectedGraphNode *, UndirectedGraphNode *>::iterator it
				= m.find(p);
			if (it != m.end()) {
				*pp = it->second;
			}
			else {
				*pp = new UndirectedGraphNode(p->label);
				(*pp)->neighbors.clear();
				(*pp)->neighbors.resize(p->neighbors.size(), 0);
				m[p] = *pp;
				for (size_t i = 0; i < p->neighbors.size(); ++i) {
					q.push(make_pair(p->neighbors[i], &(*pp)->neighbors[i]));
				}
			}
		}
		return new_node;
	}
};

int main()
{
	UndirectedGraphNode *p0 = new UndirectedGraphNode(0);
	UndirectedGraphNode *p1 = new UndirectedGraphNode(1);
	UndirectedGraphNode *p2 = new UndirectedGraphNode(2);

	p0->neighbors.push_back(p1);
	p0->neighbors.push_back(p2);

	p1->neighbors.push_back(p0);
	p1->neighbors.push_back(p2);

	p2->neighbors.push_back(p0);
	p2->neighbors.push_back(p1);
	p2->neighbors.push_back(p2);

	Solution s;
	UndirectedGraphNode *new_p0 = s.cloneGraph(p0);

	cout << new_p0->label << endl;
	for (size_t i = 0; i < new_p0->neighbors.size(); ++i) {
		cout << "       " << new_p0->neighbors[i]->label << endl;
	}

	UndirectedGraphNode *new_p1 = new_p0->neighbors[0];
	cout << new_p1->label << endl;
	for (size_t i = 0; i < new_p1->neighbors.size(); ++i) {
		cout << "       " << new_p1->neighbors[i]->label << endl;
	}

	UndirectedGraphNode *new_p2 = new_p0->neighbors[1];
	cout << new_p2->label << endl;
	for (size_t i = 0; i < new_p2->neighbors.size(); ++i) {
		cout << "       " << new_p2->neighbors[i]->label << endl;
	}

	return 0;
}
