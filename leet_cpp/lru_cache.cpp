/*
http://oj.leetcode.com/problems/lru-cache/
Thu Jan  2 14:56:39 EST 2014


LRU Cache

Design and implement a data structure for Least Recently Used (LRU)
cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if
the key exists in the cache, otherwise return -1.

set(key, value) - Set or insert the value if the key is not already
present. When the cache reached its capacity, it should invalidate
the least recently used item before inserting a new item.
*/

#include <iostream>
#include <map>

using namespace std;

class LRUCache{
private:
	struct LRUCacheNode {
		int key;
		int value;
		struct LRUCacheNode *prev;
		struct LRUCacheNode *next;
	};
	LRUCacheNode *head;
	LRUCacheNode *tail;
	int capacity;
	int size;
	map<int, LRUCacheNode *> keymap;
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
		head = new LRUCacheNode();
		tail = new LRUCacheNode();
		head->next = tail;
		tail->prev = head;
		size = 0;
	}

	~LRUCache() {
		while (head) {
			LRUCacheNode *ptmp = head;
			head = head->next;
			delete ptmp;
		}
		keymap.clear();
	}

	int get(int key) {
		map<int, LRUCacheNode *>::iterator it = keymap.find(key);
		if (it != keymap.end()) {
			LRUCacheNode *p = it->second;
			detach(p);
			attach(p);
			return p->value;
		}
		return -1;
	}

	void set(int key, int value) {
		LRUCacheNode *p;
		map<int, LRUCacheNode *>::iterator it = keymap.find(key);
		if (it != keymap.end()) {
			p = it->second;
			detach(p);
		}
		else {
			if (size < capacity) {
				p = new LRUCacheNode();
				++size;
			}
			else {
				p = tail->prev;
				keymap.erase(p->key);
				detach(p);
			}
			keymap[key] = p;
			p->key = key;
		}
		p->value = value;
		attach(p);
	}
private:
	void detach(LRUCacheNode *p) {
		p->next->prev = p->prev;
		p->prev->next = p->next;
	}
	void attach(LRUCacheNode *p) {
		p->next = head->next;
		head->next->prev = p;
		p->prev = head;
		head->next = p;
	}
};


// Using counter
struct LRUCacheLine {
	int key;
	int value;
	int access;
};

class LRUCacheCounter{
private:
	LRUCacheLine *cache;
	int access;
	int capacity;
public:
	LRUCacheCounter(int capacity) {
		cache = new LRUCacheLine[capacity];
		for (int i = 0; i < capacity; ++i) {
			cache[i].key = -1;
			cache[i].access = 0;
		}
		access = 0;
		this->capacity = capacity;
	}
	~LRUCacheCounter() { delete [] cache; }

	int get(int key) {
		for (int i = 0; i < capacity; ++i) {
			if (cache[i].key == key) {
				cache[i].access = ++access;
				return cache[i].value;
			}
		}
		return -1;
	}

	void set(int key, int value) {
		int min_access = cache[0].access;
		int index = 0;
		for (int i = 0; i < capacity; ++i) {
			if (cache[i].key == key) {
				index = i;
				break;
			}
			if (cache[i].access < min_access) {
				min_access = cache[i].access;
				index = i;
			}
		}
		cache[index].key = key;
		cache[index].value = value;
		cache[index].access = ++access;
	}
};

int main()
{
	return 0;
}
