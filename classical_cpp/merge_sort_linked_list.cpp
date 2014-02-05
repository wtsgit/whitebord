/*
http://stackoverflow.com/questions/7685/merge-sort-a-linked-list
*/
#include <random>
#include <iostream>

using namespace std;

typedef struct _aList {
	struct _aList* next;
	struct _aList* prev; // Optional.
	// some data
	int val;
} aList;

int comp(aList *one, aList *two) {
	if (one->val < two->val)
		return -1;
	if (one->val == two->val)
		return 0;
	return 1;
}

void dumpList(aList *head) {
	while (head) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

aList *merge_sort_list(aList *list,int (*compare)(aList *one,aList *two))
{
	int listSize=1,numMerges,leftSize,rightSize;
	aList *tail,*left,*right,*next;
	if (!list || !list->next) return list;  // Trivial case

	do { // For each power of two<=list length
		numMerges=0,left=list;tail=list=0; // Start at the start

		while (left) { // Do this list_len/listSize times:
			numMerges++,right=left,leftSize=0,rightSize=listSize;
			// Cut list into two halves (but don't overrun)
			while (right && leftSize<listSize) leftSize++,right=right->next;
			// Run through the lists appending onto what we have so far.
			while (leftSize>0 || (rightSize>0 && right)) {
				// Left empty, take right OR Right empty, take left, OR compare.
				if (!leftSize)                  {next=right;right=right->next;rightSize--;}
				else if (!rightSize || !right)  {next=left;left=left->next;leftSize--;}
				else if (compare(left,right)<0) {next=left;left=left->next;leftSize--;}
				else                            {next=right;right=right->next;rightSize--;}
				// Update pointers to keep track of where we are:
				if (tail) tail->next=next;  else list=next;
				// Sort prev pointer
				next->prev=tail; // Optional.
				tail=next;
			}
			// Right is now AFTER the list we just sorted, so start the next sort there.
			left=right;
		}
		// Terminate the list, double the list-sort size.
		tail->next=0,listSize<<=1;
		dumpList(list);
	} while (numMerges>1); // If we only did one merge, then we just sorted the whole list.
	return list;
}

int main() {
	random_device rd;
	default_random_engine rng(rd());
	uniform_int_distribution<int> uniform_dist(-99, 99);

	aList *head = nullptr;
	aList *tail = nullptr;
	for (size_t i = 0; i < 20; ++i) {
		aList *node = new aList();
		node->val = uniform_dist(rng);
		if (head == nullptr) {
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
	}

	dumpList(head);
	head = merge_sort_list(head, comp);
	dumpList(head);

	return 0;
}
